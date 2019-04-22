#pragma once
#ifndef _MYSTRUCT_H
#define _MYSTRUCT_H

typedef struct _Line
{
	int startX;
	int startY;
	int endX;
	int endY;
} Line;

typedef struct _Circle
{
	int midX;
	int midY;
	int radius;
}Circle;

#endif