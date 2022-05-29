#include <ECS.h>
#include <iostream>

struct A
{
    int a;
    A(int b)
    {
        a = b;
    }
};

struct B
{
    int b;
    B(int a)
    {
        b = a;
    }
};
int main()
{
    ag::ArchetypeCollection a({ ag::Component::GetID<A>(), ag::Component::GetID<B>() });
    ag::ArchetypeCollection b({ ag::Component::GetID<A>(), ag::Component::GetID<B>(), ag::Component::GetID<EntityID>() });

    for (size_t i = 0; i < 4; i++)
    {
        a.SpawnEntity(A(i * 4), B(i * 2));
    }
    EntityID one = a.SpawnEntity(A(1), B(2));
    EntityID two = b.SpawnEntity(A(5), B(3), one);

    a.ResolveBuffers();
    b.ResolveBuffers();

    std::cout << "a: " << one << std::endl;
    std::cout << "b: " << two << std::endl;

    EntityID bpointer = *b.GetComponent<EntityID>(0);
    ag::Entity wone = ag::Entity(bpointer);
    std::cout << "b points to: " << wone.Get<A>()->a << " " << wone.Get<B>()->b << std::endl;

    std::cout << "iter: " << std::endl;
    for (size_t i = 0; i < a.GetEntityCount(); i++)
    {
        std::cout << i << ": " << a.GetComponent<A>(i)->a << " " << a.GetComponent<B>(i)->b << std::endl;
    }
    a.DestroyEntity(1);
    a.ResolveBuffers();
    std::cout << "after destroying entity 1: " << std::endl;
    for (size_t i = 0; i < a.GetEntityCount(); i++)
    {
        std::cout << i << ": " << a.GetComponent<A>(i)->a << " " << a.GetComponent<B>(i)->b << std::endl;
    }
    a.DestroyEntityByID(bpointer);
    a.ResolveBuffers();
    std::cout << "after destroying what b points to: " << std::endl;
    for (size_t i = 0; i < a.GetEntityCount(); i++)
    {
        std::cout << i << ": " << a.GetComponent<A>(i)->a << " " << a.GetComponent<B>(i)->b << std::endl;
    }
}
