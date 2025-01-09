#include <vector>
#include <string>
#include <iostream>
#include <random>
#include <typeindex>
#include <memory>

struct Name
{
    std::string name;
};

struct Health
{
    int hp;
};

struct Damage
{
    int damage;
};

class ComponentBase {
private:
    std::type_index component_type;
public:
    ComponentBase(std::type_index component_type) : component_type{ component_type } {};

    virtual ~ComponentBase() = 0;

    bool operator==(std::type_index other) {
        return component_type == other;
    }

    virtual std::type_index get_type() const {
        return component_type;
    }
};
ComponentBase::~ComponentBase() {};

template<typename T>
class Component : public ComponentBase {
private:
    T val;
public:
    Component(T val) : val{ val }, ComponentBase{ typeid(T) } {};

    ~Component() override = default;

    T& get() {
        return val;
    }
};

class Entity {
private:
    std::vector<std::shared_ptr<ComponentBase>> components;

    template<typename T>
    std::shared_ptr<Component<T>> get_component() {
        for (auto& component: components) {
            if (component->get_type() == typeid(T)) {
                return std::dynamic_pointer_cast<Component<T>>(component);
            }
        }
        return nullptr;
    }

public:
    Entity() = default;
    Entity(Entity const&) = delete;
    Entity& operator=(Entity const&) = delete; 

    template<typename T>
    void add(T val) {
        components.push_back(std::make_shared<Component<T>>(val));
    }

    template<typename T>
    bool has() {
        return get_component<T>() != nullptr;
    }

    template<typename T>
    T& get() {
        return get_component<T>()->get();
    }
};

int main()
{
    int entity_count { 10 };    
    std::vector<Entity> entities(entity_count);

    // a pseudo random number generator
    std::mt19937 gen { std::random_device{}() };

    // generates a number in [0, 100)
    std::uniform_int_distribution<int> dist { 0, 99 };
    
    for (int i { 0 }; i < entity_count; ++i)
    {
        if (dist(gen) <= 50) // 50% chance to get a name
        {
            entities[i].add(Name { "Entity #" + std::to_string(i) });
        }

        if (dist(gen) <= 80) // 80% chance to get health
        {
            entities[i].add(Health{dist(gen)});
        }

        if (dist(gen) <= 75) // 75% chance to get damage
        {
            entities[i].add(Damage{dist(gen)});
        }
    }

    // A system for processing all entities with the Name component
    std::cout << "Named entities: " << std::endl;
    for (Entity& entity : entities)
    {
        if (entity.has<Name>())
        {
            std::cout << " - " << entity.get<Name>().name << std::endl;
        }
    }

    // A system for processing all entities with both Health and Damage
    std::cout << "Battle ready entities: " << std::endl;
    for (std::size_t i { 0 }; i < entities.size(); ++i)
    {
        Entity& entity { entities[i] };
        if (entity.has<Health>() && entity.has<Damage>())
        {
            std::cout << " - " << i << ": has " << entity.get<Health>().hp
                      << " hp and deals " << entity.get<Damage>().damage << " damage"
                      << std::endl;
        }
    }
}