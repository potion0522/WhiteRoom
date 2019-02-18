#include "CollideManager.h"
#include "SphereCollider.h"
#include "SquareCollider.h"

CollideManager::CollideManager( ) {
}

CollideManager::~CollideManager( ) {
}

void CollideManager::update( ) {
	detectDynamicToDynamicObject( );
	detectDynamicToStaticObject( );
}

void CollideManager::addDynamicCollider( SphereColliderWeakPtr collider ) {
	_dynamic_sphere_obj.push_back( collider );
}

void CollideManager::addStaticCollider( SphereColliderPtr collider ) {
	_static_sphere_obj.push_back( collider );
}

void CollideManager::addStaticCollider( SquareColliderPtr collider ) {
	_static_square_obj.push_back( collider );
}

void CollideManager::detectDynamicToDynamicObject( ) {
	std::list< SphereColliderWeakPtr >::iterator ite1 = _dynamic_sphere_obj.begin( );
	for ( ite1; ite1 != _dynamic_sphere_obj.end( ); ite1++ ) {
		SphereColliderPtr collider1 = ( *ite1 ).lock( );
		if ( !collider1 ) {
			continue;
		}

		{ // sphere → sphere
			std::list< SphereColliderWeakPtr >::iterator ite2 = ite1;
			ite2++;
			for ( ite2; ite2 != _dynamic_sphere_obj.end( ); ite2++ ) {
				SphereColliderPtr collider2 = ( *ite2 ).lock( );
				if ( !collider2 ) {
					continue;
				}
				bool collide = isCollideSphereAndSphere( collider1, collider2 );
				if ( collide ) {
					collider1->onColliderEnter( collider2 );
					collider2->onColliderEnter( collider1 );
				}
			}
		}
	}
}

void CollideManager::detectDynamicToStaticObject( ) {
	std::list< SphereColliderWeakPtr >::iterator ite = _dynamic_sphere_obj.begin( );
	for ( ite; ite != _dynamic_sphere_obj.end( ); ite++ ) {
		SphereColliderPtr collider1 = ( *ite ).lock( );
		if ( !collider1 ) {
			continue;
		}

		{ // sphere → sphere
			for ( int i = 0; i < _static_sphere_obj.size( ); i++ ) {
				SphereColliderPtr collider2 = _static_sphere_obj[ i ];

				bool collide = isCollideSphereAndSphere( collider1, collider2 );

				if ( collide ) {
					collider1->onColliderEnter( collider2 );
					collider2->onColliderEnter( collider1 );
				}
			}
		}

		{ // sphere → square
			for ( int i = 0; i < _static_square_obj.size( ); i++ ) {
				SquareColliderPtr collider2 = _static_square_obj[ i ];

				bool collide = isCollideSphereAndSquare( collider1, collider2 );

				if ( collide ) {
					collider1->onColliderEnter( collider2 );
					collider2->onColliderEnter( collider1 );
				}
			}
		}
	}
}

bool CollideManager::isCollideSphereAndSphere( SphereColliderPtr collider1, SphereColliderPtr collider2 ) {
	Vector pos1 = collider1->getPos( );
	double radius1 = collider1->getRadius( );

	Vector pos2 = collider2->getPos( );
	double radius2 = collider2->getRadius( );

	if ( ( pos2 - pos1 ).getLength2( ) < ( radius1 + radius2 ) * ( radius1 + radius2 ) ) {
		return true;
	}
	return false;
}

bool CollideManager::isCollideSphereAndSquare( SphereColliderPtr collider1, SquareColliderPtr collider2 ) {
	Vector pos1 = collider1->getPos( );
	double radius1 = collider1->getRadius( );

	Vector pos2 = collider2->getPos( );
	Vector norm = collider2->getNorm( );
	double width = collider2->getWidth( );
	double height = collider2->getHeight( );

	// 表裏どちらにあるかの判定
	double dot = norm.dot( pos1 - pos2 );
	if ( dot > 0 ) {
		return false;
	}

	// 面の座標の割り出し 　0:左上 1:右上 2:左下 3:右下
	Vector horizontal = norm.cross( Vector( norm.x, norm.y + 100, norm.z ) ).normalize( ); // 横
	Vector vertical = norm.cross( horizontal ).normalize( ); //縦
	Vector square_pos[ 4 ] = {

	};

	return false;
}