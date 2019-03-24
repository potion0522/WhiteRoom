#pragma once

enum FLOOR {
	FLOOR_GF,
	FLOOR_1,
	FLOOR_2,
	FLOOR_3,
	FLOOR_4,
	FLOOR_5,
	MAX_FLOOR,
};

const FLOOR ELEVATOR_INIT_FLOOR = FLOOR_2;
const FLOOR PLAYER_INIT_FLOOR   = FLOOR_2; 

enum OBJECT_TAG {
	OBJECT_TAG_NONE,
	OBJECT_TAG_PLAYER,
	OBJECT_TAG_WALL,
	OBJECT_TAG_ELEVATOR,
	OBJECT_TAG_ELEVATOR_SIDE_WALL, // floor
	OBJECT_TAG_ELEVATOR_DOOR,      // elevator
	OBJECT_TAG_SPHERE,
	OBJECT_TAG_Q2SPHERE_1,
	OBJECT_TAG_Q2SPHERE_2,
	OBJECT_TAG_Q2SPHERE_3,
	OBJECT_TAG_Q2SPHERE_4,
	OBJECT_TAG_Q2SPHERE_5,
};

const int SCREEN_WIDTH  = 1920;
const int SCREEN_HEIGHT = 1080;

const int FLOOR_HEIGHT = 3000;  // 部屋の高さ( 床から )
const int FLOOR_WIDTH  = 15000; // 部屋の幅( 全体 )
const int FLOOR_TO_FLOOR_SPACE = 1000; // 部屋同士の間隔
const int FLOOR_TO_FLOOR_SPACE_AND_FLOOR_HEIGHT = FLOOR_HEIGHT + FLOOR_TO_FLOOR_SPACE;

const int ELEVATOR_HEIGHT = FLOOR_HEIGHT; // 部屋のサイズと同じ
const int ELEVATOR_WIDTH  = 2000; // エレベーターの幅( 全体 )
const int ELEVATOR_TO_FLOOR_SPACE = 20; // エレベーターとフロアとの間隔
const double ELEVATOR_WALL_OVER_SIZE = 300; // エレベーターを覆う壁がエレベーターの部屋の大きさよりすこし大きくするための値
const double ELEVATOR_INIT_X = FLOOR_WIDTH / 2 + ELEVATOR_WIDTH / 2 + ELEVATOR_TO_FLOOR_SPACE;
const double ELEVATOR_INIT_Y = ELEVATOR_INIT_FLOOR * -FLOOR_TO_FLOOR_SPACE_AND_FLOOR_HEIGHT;
const double ELEVATOR_INIT_Z = 0;

const double SPHERE_OBJECT_RADIUS = 650.0;

const int    METER_TO_MIRI_UNIT = 1000;
const double MIRI_TO_METER_UNIT = 0.001;


const int CONSOLE_WIDTH = 1920;
const int CONSOLE_HEIGHT = 1080;

// 月ごとの日数
const int DAY_IN_MONTH[ 12 ] = {
	31, //  1月
	28, //  2月
	31, //  3月
	30, //  4月
	31, //  5月
	30, //  6月
	31, //  7月
	31, //  8月
	30, //  9月
	31, // 10月
	30, // 11月
	31, // 12月
};
