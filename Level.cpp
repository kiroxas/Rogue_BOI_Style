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

	Hero_type e = Hero_type(new Character(pool.getImage("isaac"),cm));
	//heroes.emplace_back(std::unique_ptr<Character>(pool.getImage("isaac"),cm));
	e->setProperties(properties::defs::Triggering_global);
	e->setTeam(1);
	hero_move = g_i.Suscribable<Events::Move, void(std::pair<int,int>)>::Suscribe(std::bind(&ICharacter::Move,e.get(),std::placeholders::_1));
	hero_shoot = g_i.Suscribable<Events::Shoot,void(void)>::Suscribe(std::bind(&ICharacter::shoot,e.get()));
	//Leave Room
	assign_room = maze->getCurrentRoom()->Suscribe(std::bind(&Level::ReAssignRoom, this, std::placeholders::_1));
	maze->getCurrentRoom()->setVisited();
	stats.addVisited();

	maze->getCurrentRoom()->addCharacter(std::move(e));
}

const Maze& Level::getMaze() const
{
	return *maze;
}

std::vector<Level::Hero_type> Level::getCharacters()
{
	return maze->getCurrentRoom()->getCharacters();
}

const std::vector<Level::Hero_type>& Level::peekAtCharacters() const
{
	return maze->getCurrentRoom()->peekAtCharacters();
}

void Level::ReAssignRoom(Direction d)
{
	maze->getCurrentRoom()->desassignCM();
	auto heroes = maze->getCurrentRoom()->getCharacters(); //transfers ownership
	maze->Go(d);
	auto room = maze->getCurrentRoom();
	if(!room->hasBeenVisited())
		stats.addVisited();
	room->assignCM(cm);
	std::cout << "Assigned CM" << std::endl;
	room->setVisited();
	stats.addEnnemiesEncountered(room->getNumberOfEnnemies());
	//LeaveRoom
	assign_room = room->Suscribe(std::bind(&Level::ReAssignRoom, this, std::placeholders::_1));
	if(room->getRoomType() == BOSS)
		exit_level = room->RoomEmpty::Suscribe(std::bind(&ClearedLevel::Notify, this));

	for(auto&& e : heroes)
	{
		std::cout << "Setting 400;300" << std::endl;
		e->setPosition(400,300);
		maze->getCurrentRoom()->addCharacter(std::move(e));
	}
}

void Level::update()
{
	auto room = maze->getCurrentRoom();
	room->update();
	for(auto e: callbacks)
		e();
	auto& heroes = room->peekAtCharacters();

	if(std::all_of(std::begin(heroes), std::end(heroes), [](const Hero_type& e){ return e->isDead();}))
		HeroAreDead::Notify();
}
