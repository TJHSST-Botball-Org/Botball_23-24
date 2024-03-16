#include <kipr/wombat.h>
#include <Roomba.h>

void Roomba::move(int distance, int speed)
{
    int factor = distance > 0 ? -1 : 1;
    set_create_distance(0);

    while (factor * get_create_distance() < distance)          // if forward, get_create_distance() returns negative
        create_drive_direct(-factor * speed, -factor * speed); // if forward, factor will be negative meaning we need to minus

    create_stop();
}

void Roomba::rotate(float angle)
{
}
