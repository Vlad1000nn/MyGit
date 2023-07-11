#define NOMINMAX
#include <iostream>
#include <cstdlib>
#include <string>
#include <string_view>
#include <limits>
#include <array>
#include <random>
#include <windows.h>

using namespace std;

// Пространство имён для рандомизации
namespace Random
{
	// Создаём генератор
	std::mt19937 mt{ std::random_device{}() };

	// Функция получения рандомного числа из диапазона
	int get(int min, int max)
	{
		std::uniform_int_distribution<> die{ min, max };
		return die(mt);
	}
}


void SetColor(int text, int background)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}


// Игнорирование неверного ввода
void IgnoreLine()
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


// Класс существа
class Creature
{
protected:
	// Имя
	const string_view name;
	// Обозначение(символика)
	const char symbol;
	// Здоровье
	unsigned int hp;
	// Урон
	unsigned int damage;
	// Количество золота
	unsigned int gold;

public:
	// Базовый конструктор
	Creature(string_view _name, const char _symbol, const int _hp, const int _damage, const int _gold)
		: name(_name)
		, symbol(_symbol)
	{
		// Если хп 0 и ниже существо мертво, урон и золото неотрицательны
		if (_hp < 1 || _damage < 0 || _gold < 0)
		{
			cout << "Something went wrong, Creature was broken\n";
			std::exit(0);
		}
		// Всё остальное присваиваем
		this->hp = _hp;
		this->damage = _damage;
		this->gold = _gold;
	}

	// Геттеры
	string_view getName() const
	{
		return this->name;
	}

	char getSymbol() const
	{
		return this->symbol;
	}

	int getHealth() const
	{
		return this->hp;
	}

	int getDamage() const
	{
		return this->damage;
	}

	int getGold() const
	{
		return this->gold;
	}

	// Уменьшение здоровья
	void reduceHealth(const int value)
	{
		// Нельзя уменьшить на отрицательное
		if (value < 0)
		{
			cout << "Something went wrong, damage < 0\n";
			std::exit(0);
		}
		// Если не мертвый
		if (!isDead())
		{
			// Если урон меньше чем у существа хп, то отнимаем
			if (value <= static_cast<int>(hp))
				hp -= value;
			// Иначе мы умерли
			else
				hp = 0;
		}
	}

	// Добавление здоровья
	void addHealth(const int value)
	{
		// Нельзя добавить отрицательное здоровье
		if (value < 0)
		{
			cout << "Something went wrong, potion < 0\n";
			std::exit(0);
		}
		// Добавляем
		hp += value;
	}

	// Добавление урона
	void addDamage(const int value)
	{
		// Нельзя добавлять отрицательный урон
		if (value < 0)
		{
			std::cout << "Something went wrong, adding damage <0\n";
			std::exit(0);
		}
		// Добавляем
		damage += value;
	}

	// Проверка умерло ли существо
	bool isDead() const
	{
		return !hp;
	}

	// Добавление существу золота
	void addGold(const int value)
	{
		// Нельзя добавить отрицательное количество золота
		if (value < 0)
		{
			cout << "Something went wrong, you try to minus gold\n";
			std::exit(0);
		}
		// Прибавляем
		gold += value;
	}

};

// Класс игрок
class Player : public Creature
{
private:
	// Уровень игрока(стартовый 1)
	unsigned int level{ 1 };

public:
	// Базовый конструктор
	Player(string_view _name) : Creature(_name, '@', 10, 1, 0)
	{ }

	// Повышение уровня
	void LevelUp()
	{
		++level;
		++damage;
	}

	// Геттер
	int getLevel() const
	{
		return this->level;
	}

	// Если уровень 20, то победа
	bool hasWon() const
	{
		return level == 20;
	}
};

// Класс монстр
class Monster : public Creature
{
public:
	// Типы монстров
	enum class MonsterType
	{
		dragon,
		orc,
		slime,
		max_monster_types,
	};

private:
	// Базовая таблица с характеристиками монстров
	static const Creature& getDefaultCreature(MonsterType type)
	{
		static const std::array<Creature, static_cast<std::size_t>(MonsterType::max_monster_types)> monsterData
		{
		  {
			{ "dragon", 'D', 20, 4, 100 },
			{ "orc", 'o', 4, 2, 25 },
			{ "slime", 's', 1, 1, 10 }
			}
		};

		return monsterData.at(static_cast<std::size_t>(type));
	}

public:
	// Базовый конструктор
	Monster(MonsterType type) : Creature(getDefaultCreature(type))
	{ }

	// Получение рандомного монстра
	static const MonsterType getRandomMonster()
	{
		return static_cast<MonsterType>(Random::get(0, static_cast<int>(MonsterType::max_monster_types) - 1));
	}

};

// Класс зелий
class Potion
{
public:

	// Сила зелья
	enum class PotionPower
	{
		Small,
		medium,
		large,
		max_potionpower_types,
	};

	// Тип зелья
	enum class PotionType
	{
		hill,
		strength,
		posion,
		max_potion_types,
	};

private:
	// Сила эффекта
	PotionPower power;
	// Тип эффекта
	PotionType type;

public:
	// Базовый конструктор
	Potion(const PotionType _type, PotionPower _power)
		: type(_type)
		, power(_power)
	{ }

	// Рандомный тип зелья
	static const PotionType getRandomPotion()
	{
		return static_cast<PotionType>(Random::get(0, static_cast<int>(PotionType::max_potion_types) - 1));
	}

	// Рандомная сила зелья
	static const PotionPower getRandomPotionPower()
	{
		return static_cast<PotionPower>(Random::get(0, static_cast<int>(Potion::PotionPower::max_potionpower_types) - 1));
	}

	// Получаем тип зелья
	PotionType getPotionType() const
	{
		return this->type;
	}

	// Получаем силу зелья
	PotionPower getPotionPower() const
	{
		return this->power;
	}

	// Получаем прибавку зелья
	unsigned int getValue() const
	{
		switch (type)
		{
		case PotionType::hill:
		{
			switch (power)
			{
			case PotionPower::Small:
			{
				return 1;
			}
			case PotionPower::medium:
			{
				return 3;
			}
			case PotionPower::large:
			{
				return 5;
			}
			default:
			{
				std::cout << "Something went wrong, unknown power of potion\n";
				std::exit(0);
			}
			}
		}
		case PotionType::strength:
		{
			switch (power)
			{
			case PotionPower::Small:
			{
				return 1;
			}
			case PotionPower::medium:
			{
				return 2;
			}
			case PotionPower::large:
			{
				return 3;
			}
			default:
			{
				std::cout << "Something went wrong, unknown power of potion\n";
				std::exit(0);
			}
			}
		}
		case PotionType::posion:
		{
			switch (power)
			{
			case PotionPower::Small:
			{
				return 1;
			}
			case PotionPower::medium:
			{
				return 3;
			}
			case PotionPower::large:
			{
				return INT_MAX;
			}
			default:
			{
				std::cout << "Something went wrong, unknown power of potion\n";
				std::exit(0);
			}
			}
		}
		default:
		{
			std::cout << "Something went wrong, unknown potion type\n";
			std::exit(0);
		}
		}
	}
};

// Попытка убежать
bool try_to_escape()
{
	return Random::get(0, 1);
}

// Вывод мощности зелья
void printPower(const Potion& potion)
{
	switch (potion.getPotionPower())
	{
	case Potion::PotionPower::Small:
	{
		std::cout << "small ";
		break;
	}
	case Potion::PotionPower::medium:
	{
		std::cout << "medium ";
		break;
	}
	case Potion::PotionPower::large:
	{
		std::cout << "large ";
		break;
	}
	default:
	{
		std::cout << "Something went wrong, unknown power of potion\n";
		break;
	}
	}
}

// Выпить зелье
void drink(Player& player)
{
	Potion potion{ Potion::getRandomPotion(), Potion::getRandomPotionPower() };

	switch (potion.getPotionType())
	{
	case Potion::PotionType::hill:
	{
		std::cout << "Nice! That was ";
		printPower(potion);
		SetColor(2, 0);
		std::cout << "hill";
		SetColor(15, 0);
		std::cout << " potion, you got " << potion.getValue() << " hp.\n";
		player.addHealth(potion.getValue());
		break;
	}
	case Potion::PotionType::strength:
	{
		std::cout << "Cool! That was ";
		printPower(potion);
		SetColor(6, 0);
		std::cout << "strength";
		SetColor(15, 0);
		std::cout << " potion, you got " << potion.getValue() << " damage to your sword.\n";
		player.addDamage(potion.getValue());
		break;
	}
	case Potion::PotionType::posion:
	{
		std::cout << "Oh no! That was ";
		printPower(potion);
		SetColor(4, 0);
		std::cout << "posion";
		SetColor(15, 0);
		std::cout << ".. ";
		if (potion.getValue() == INT_MAX)
			std::cout << "you lost all your hp.\n";
		else
			std::cout << "you lost " << potion.getValue() << " hp.\n";
		player.reduceHealth(potion.getValue());
	}
	}
}

// Битва
void Attack(Player& player, Monster& monster)
{
	// Бьём монстра
	monster.reduceHealth(player.getDamage());
	SetColor(2, 0);
	std::cout << "You hit the " << monster.getName() << " for " << player.getDamage() << " damage.\n";
	SetColor(15, 0);

	// Если монстр умер
	if (monster.isDead())
	{
		// Начисляем плюшки
		player.addGold(monster.getGold());
		player.LevelUp();
		std::cout << "You killed the " << monster.getName() << ".\n";
		SetColor(6, 0);
		std::cout << "You are now level " << player.getLevel() << ".\nYou found " << monster.getGold() << " gold.\n";
		SetColor(15, 0);

		// Шанс на выпадение зелья
		int r{ Random::get(0,2) };
		if (!r)
		{
			char choise;
			SetColor(6, 0);
			std::cout << "\nYou found unknown potion.\n";
			SetColor(15, 0);
			while (true)
			{
				std::cout << "Do you want to (D)rink it or (N)ot? ";
				cin >> choise;
				if (choise == 'd' || choise == 'D' || choise == 'n' || choise == 'N')
					break;
				else
				{
					IgnoreLine();
					SetColor(12, 0);
					std::cout << "Wrong input!\n";
					SetColor(15, 0);
				}
			}
			if (choise == 'D' || choise == 'd')
			{
				drink(player);
			}
		}
	}
	else
	{
		// Монстр атакует игрока
		player.reduceHealth(monster.getDamage());
		SetColor(4, 0);
		std::cout << "The " << monster.getName() << " hit you " << monster.getDamage() << " damage.\n";
		SetColor(15, 0);
	}
}

// Битва с монстром
void monsterFignt(Player& player, Monster& monster)
{
	while (true)
	{
		char choise;
		while (true)
		{
			std::cout << "(R)un or (F)ight: ";
			cin >> choise;

			if (choise == 'r' || choise == 'R' || choise == 'f' || choise == 'F')
				break;
			else
			{
				IgnoreLine();
				SetColor(12, 0);
				std::cout << "Wrong input!\n";
				SetColor(15, 0);
			}
		}
		if (choise == 'r' || choise == 'R')
		{
			if (try_to_escape())
			{
				SetColor(2, 0);
				std::cout << "You successfully fled.\n";
				SetColor(15, 0);
				return;
			}
			else
			{
				SetColor(4, 0);
				std::cout << "You failed to flee.\nThe " << monster.getName() << " hit you " << monster.getDamage() << " damage.\n\n";
				SetColor(15, 0);
				player.reduceHealth(monster.getDamage());
			}
		}
		else if (choise == 'f' || choise == 'F')
		{
			Attack(player, monster);
		}

		if (player.isDead() || monster.isDead())
			return;
	}
}

// Шаг игры
void step(Player& player)
{
	Monster monster{ Monster::getRandomMonster() };

	std::cout << "\nYou have encountered a " << monster.getName() << " (" << monster.getSymbol() << ").\n";

	monsterFignt(player, monster);
}

// Вывод при смерти
void printDead(const Player& player)
{
	SetColor(6, 0);
	std::cout << "\nYou died at level " << player.getLevel() << " and with " << player.getGold() << " gold.\nToo bad you can't take it with you!\n";
	SetColor(15, 0);
}

// Вывод при победе
void printWon(const Player& player)
{
	SetColor(6, 0);
	std::cout << "\nYou won the game with " << player.getGold() << " gold!\n";
	SetColor(15, 0);
}

int main()
{
	// Ввод имени
	string Playername;
	std::cout << "Enter your name: ";
	cin >> Playername;

	// Создание игрока
	Player player(Playername);

	// Приветствие
	std::cout << "Welcome, " << player.getName() << "!\n";

	// Цикл игры
	while (true)
	{
		step(player);

		if (player.isDead())
		{
			printDead(player);
			break;
		}
		else if (player.hasWon())
		{
			printWon(player);
			break;
		}
	}

	std::cout << '\n';
	system("pause");

	return 0;
}