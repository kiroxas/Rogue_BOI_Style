#include "Level.h"
#include "Characters/Character.h"

Level::Level(const ImagePool& p, Input::GameInput& gi, GameInfo& s) :
pool(p),
cm(new CollisionManager(s)),
g_i(gi),
stats(s)
{
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<int> int_distribution(0,10);

	std::unique_ptr<AbstractMazeGenerator> g(new NormalMazeGenerator(pool));
	maze = (g->CreateMaze(int_distribution(generator)));
	maze->getCurrentRoom()->assignCM(cm);
	stats.addCreated(maze->getNumberRooms());
	stats.addEnnemiesEncountered(maze->getCurrentRoom()->getNumberOfEnnemies());
	heroes.emplace_back(std::make_shared<Character>(pool.getImage("isaac"),cm));
	heroes.back()->setProperties(properties::defs::Triggering_global);
	hero_move = g_i.Suscribable<Events::Move, void(std::pair<int,int>)>::Suscribe(std::bind(&ICharacter::Move,heroes.back().get(),std::placeholders::_1));
	hero_shoot = g_i.Suscribable<Events::Shoot,void(void)>::Suscribe(std::bind(&ICharacter::shoot,heroes.back().get()));
	//Leave Room
	assign_room = maze->getCurrentRoom()->Suscribe(std::bind(&Level::ReAssignRoom, this, std::placeholders::_1));
	maze->getCurrentRoom()->setVisited();
	stats.addVisited();

	for(auto& e : heroes)
		maze->getCurrentRoom()->addCharacter(e);
}

const Maze& Level::getMaze() const
{
	return *maze;
}

const std::vector<std::shared_ptr<ICharacter>>& Level::getCharacters() const
{
	return maze->getCurrentRoom()->getCharacters();
}

void Level::ReAssignRoom(Direction d)
{
	maze->getCurrentRoom()->desassignCM();
	maze->Go(d);
	auto room = maze->getCurrentRoom();
	if(!room->hasBeenVisited())
		stats.addVisited();
	room->assignCM(cm);
	room->setVisited();
	stats.addEnnemiesEncountered(room->getNumberOfEnnemies());
	//LeaveRoom
	assign_room = room->Suscribe(std::bind(&Level::ReAssignRoom, this, std::placeholders::_1));
	if(room->getRoomType() == BOSS)
		exit_level = room->RoomEmpty::Suscribe(std::bind(&ClearedLevel::Notify, this));

	for(auto& e : heroes)
	{
		e->setPosition(400,400);
		maze->getCurrentRoom()->addCharacter(e);
	}
}

void Level::update()
{
	maze->getCurrentRoom()->update();
	for(auto e: callbacks)
		e();

	if(std::all_of(std::begin(heroes), std::end(heroes), [](const Hero_type& e){ return e->isDead();}))
		HeroAreDead::Notify();
}