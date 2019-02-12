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

const int FLOOR_HEIGHT = 3000; // �����̍���( ������ )
const int FLOOR_WIDTH  = 5000; // �����̕�( ���S���� )

const int ELEVATOR_HEIGHT = FLOOR_HEIGHT; // �����̃T�C�Y�Ɠ���
const int ELEVATOR_WIDTH  = 1500; // �G���x�[�^�[�̕�( ���S���� )

const int    METER_TO_MIRI_UNIT = 1000;
const double MIRI_TO_METER_UNIT = 0.001;


const int CONSOLE_WIDTH = 1920;
const int CONSOLE_HEIGHT = 1080;
