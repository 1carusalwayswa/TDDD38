/*
Essentially, we just want a variable could flexibly store some known type(Name, Health, Damage),
So, obviously, we could use std::variant to do this work
and using get_if<T> could easily get T from specific variant,
if this variant doesn't store T, get_if will return a nullptr.
*/
#include <typeindex>
#include <vector>
#include <string>
#include <iostream>
#include <random>
#include <variant>


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

class Entity
{
private:
    std::vector<std::variant<Name, Health, Damage>> components;

    template <typename T>
    T* get_component() {
        for (auto& component: components) {
            auto tmp_ptr = std::get_if<T>(&component);
            if (tmp_ptr != nullptr) {
                return tmp_ptr;
            }
        }
        return nullptr;
    }
public:
    Entity() = default;
    Entity(Entity const&) = delete;
    Entity& operator=(Entity const&) = delete;

    template <typename T>
    void add(T&& val) {
        components.emplace_back(std::forward<T>(val));
    }

    template <typename T>
    bool has() {
        T* tmp_ptr = get_component<T>();
        return tmp_ptr != nullptr;
    }

    template <typename T>
    T& get() {
        return *get_component<T>();
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