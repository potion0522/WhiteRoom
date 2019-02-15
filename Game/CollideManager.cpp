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

void CollideManager::addDynamicCollider( SquareColliderWeakPtr collider ) {
	_dynamic_square_obj.push_back( collider );
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

		{ // sphere Å® sphere
			std::list< SphereColliderWeakPtr >::iterator ite2 = ite1;
			ite2++;
			for ( ite2; ite2 != _dynamic_sphere_obj.end( ); ite2++ ) {
				SphereColliderPtr collider2 = ( *ite2 ).lock( );
				if ( !collider2 ) {
					continue;
				}

				bool collide = isCollideSphereAndSphere( collider1, collider2 );
				if ( collide ) {
					collider1->onColliderEnter( collider2->getTag( ) );
					collider2->onColliderEnter( collider1->getTag( ) );
				}
			}
		}

		
		{ // sphere Å® square
			std::list< SquareColliderWeakPtr >::iterator ite2 = _dynamic_square_obj.begin( );
			for ( ite2; ite2 != _dynamic_square_obj.end( ); ite2++ ) {
				SquareColliderPtr collider2 = ( *ite2 ).lock( );
				if ( !collider2 ) {
					continue;
				}

				bool collide = isCollideSphereAndSquare( collider1, collider2 );
				if ( collide ) {
					collider1->onColliderEnter( collider2->getTag( ) );
					collider2->onColliderEnter( collider1->getTag( ) );
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

		{ // sphere Å® sphere
			for ( int i = 0; i < _static_sphere_obj.size( ); i++ ) {
				SphereColliderPtr collider2 = _static_sphere_obj[ i ];

				bool collide = isCollideSphereAndSphere( collider1, collider2 );

				if ( collide ) {
					collider1->onColliderEnter( collider2->getTag( ) );
					collider2->onColliderEnter( collider1->getTag( ) );
				}
			}
		}
	}
}

bool CollideManager::isCollideSphereAndSphere( SphereColliderPtr collider1, SphereColliderPtr collider2 ) {
	Vector pos1 = collider1->getPos( );
	Vector pos2 = collider2->getPos( );
	double radius1 = collider1->getRadius( );
	double radius2 = collider2->getRadius( );

	if ( ( pos2 - pos1 ).getLength2( ) < ( radius1 + radius2 ) * ( radius1 + radius2 ) ) {
		return true;
	}
	return false;
}

bool CollideManager::isCollideSphereAndSquare( SphereColliderPtr collider1, SquareColliderPtr collider2 ) {
	Vector pos1 = collider1->getPos( );
	Vector pos2 = collider2->getPos( );
	double radius1 = collider1->getRadius( );
	double width = collider2->getWidth( );
	double height = collider2->getHeight( );


	return false;
}