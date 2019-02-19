#pragma once

enum FLOOR {
	FLOOR_GF,
	FLOOR_1,
	FLOOR_2,
	FLOOR_3,
	FLOOR_4,
	FLOOR_5,
	FLOOR_HF,
	MAX_FLOOR,
};

enum OBJECT_TAG {
	OBJECT_TAG_NONE,
	OBJECT_TAG_PLAYER,
	OBJECT_TAG_WALL,
	OBJECT_TAG_ELEVATOR_DOOR
};

const int SCREEN_WIDTH  = 1920;
const int SCREEN_HEIGHT = 1080;

const int FLOOR_HEIGHT = 3000;  // 部屋の高さ( 床から )
const int FLOOR_WIDTH  = 10000; // 部屋の幅( 全体 )

const int ELEVATOR_HEIGHT = FLOOR_HEIGHT; // 部屋のサイズと同じ
const int ELEVATOR_WIDTH  = 1500; // エレベーターの幅( 中心から )

const int    METER_TO_MIRI_UNIT = 1000;
const double MIRI_TO_METER_UNIT = 0.001;


const int CONSOLE_WIDTH = 1920;
const int CONSOLE_HEIGHT = 1080;
