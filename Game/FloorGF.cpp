#include "FloorGF.h"



FloorGF::FloorGF( CollideManagerPtr collide_manager, ElevatorAnnounceObservablePtr observable ) :
Floor( collide_manager, observable, FLOOR_GF ) {
}


FloorGF::~FloorGF( ) {
}
