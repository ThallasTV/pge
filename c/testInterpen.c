#include <stdio.h>
#include <stdbool.h>
#include "Gcoord.h"
#include "Ginterpen.h"

void circleTest (void)
{
  interpen_interCircle a;
  interpen_interCircle b;

  a.radius = 0.5;
  a.center = coord_initCoord (6.0, 7.0);

  b.radius = 0.5;
  b.center = coord_initCoord (6.75, 7.0);

  if (interpen_circleCollide (a, b) == true)
    printf("There has been a collision\n");
  else
    printf("There has not been a collision\n");

  //----------------------------------------------//

  a.radius = 0.5;
  a.center = coord_initCoord (6.0, 7.0);

  b.radius = 0.5;
  b.center = coord_initCoord (6.0, 6.25);

  if (interpen_circleCollide (a, b) == true)
    printf("There has been a collision\n");
  else
    printf("There has not been a collision\n");

}


void circleSegmentTest (void)
{
  interpen_interCircle c;
  segment_Segment s;
  unsigned int ptn;
  history_whereHit at;
  coord_Coord point;

  c = interpen_initCircle (0.5, coord_initCoord (0.5, 0.5));
  s = segment_initSegment (coord_initCoord (0.2, 0.48), coord_initCoord (0.6, 0.48));

  if (interpen_circleSegmentCollide (c, s, &point, &at, &ptn) == true)
    printf("There has been a circle-segment collision\n");
  else
    printf("There has not been a circle-segment collision\n");


}

void segmentSegmentTest (void)
{
  segment_Segment a;
  segment_Segment b;
  coord_Coord p;
  history_whereHit atA;
  history_whereHit atB;
  unsigned int ptnA;
  unsigned int ptnB;

  a = segment_initSegment (coord_initCoord (2.0, 5.0), coord_initCoord (8.0, 5.0));
  b = segment_initSegment (coord_initCoord (5.0, 2.0), coord_initCoord (5.0, 8.0));

  if (interpen_segmentsCollide (a, b, &p, &atA, &atB, &ptnA, &ptnB) == true)
    printf("There has been a segment-segment collision\n");
  else
    printf("There has not been a segment-segment collision\n");



}


int main()
{
  circleTest();
  circleSegmentTest();
  segmentSegmentTest();



}
