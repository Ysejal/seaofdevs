# Sea of Devs

## Select one of 4 random directions with rand() :

```c
int x = rand() % 4;

switch(x)
{
   case 0:
      movePlayer(map, &positionPlayer, UP);
      break;

   case 1:
      movePlayer(map, &positionPlayer, DOWN);
      break;

   case 2:
      movePlayer(map, &positionPlayer, LEFT);
      break;

   case 3:
      movePlayer(map, &positionPlayer, RIGHT);
      break;
}
```

