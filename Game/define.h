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

const int FLOOR_HEIGHT = 3000;  // �����̍���( ������ )
const int FLOOR_WIDTH  = 15000; // �����̕�( �S�� )
const int FLOOR_TO_FLOOR_SPACE = 1000; // �������m�̊Ԋu
const int FLOOR_TO_FLOOR_SPACE_AND_FLOOR_HEIGHT = FLOOR_HEIGHT + FLOOR_TO_FLOOR_SPACE;

const int ELEVATOR_HEIGHT = FLOOR_HEIGHT; // �����̃T�C�Y�Ɠ���
const int ELEVATOR_WIDTH  = 2000; // �G���x�[�^�[�̕�( �S�� )
const int ELEVATOR_TO_FLOOR_SPACE = 20; // �G���x�[�^�[�ƃt���A�Ƃ̊Ԋu
const double ELEVATOR_WALL_OVER_SIZE = 300; // �G���x�[�^�[�𕢂��ǂ��G���x�[�^�[�̕����̑傫����肷�����傫�����邽�߂̒l
const double ELEVATOR_INIT_X = FLOOR_WIDTH / 2 + ELEVATOR_WIDTH / 2 + ELEVATOR_TO_FLOOR_SPACE;
const double ELEVATOR_INIT_Y = ELEVATOR_INIT_FLOOR * -FLOOR_TO_FLOOR_SPACE_AND_FLOOR_HEIGHT;
const double ELEVATOR_INIT_Z = 0;

const double SPHERE_OBJECT_RADIUS = 650.0;

const int    METER_TO_MIRI_UNIT = 1000;
const double MIRI_TO_METER_UNIT = 0.001;


const int CONSOLE_WIDTH = 1920;
const int CONSOLE_HEIGHT = 1080;

// �����Ƃ̓���
const int DAY_IN_MONTH[ 12 ] = {
	31, //  1��
	28, //  2��
	31, //  3��
	30, //  4��
	31, //  5��
	30, //  6��
	31, //  7��
	31, //  8��
	30, //  9��
	31, // 10��
	30, // 11��
	31, // 12��
};
