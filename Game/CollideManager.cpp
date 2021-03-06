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
		{ // sphere → sphere
			std::list< SphereColliderWeakPtr >::iterator ite2 = ite1;
			ite2++;
			for ( ite2; ite2 != _dynamic_sphere_obj.end( ); ite2++ ) {
				SphereColliderPtr collider1 = ( *ite1 ).lock( );
				SphereColliderPtr collider2 = ( *ite2 ).lock( );
				if ( !collider1 || !collider2 ) {
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

		{ // sphere → sphere
			for ( int i = 0; i < _static_sphere_obj.size( ); i++ ) {
				SphereColliderPtr collider1 = ( *ite ).lock( );
				SphereColliderPtr collider2 = _static_sphere_obj[ i ];

				if ( !collider1 ) {
					break;
				}

				bool collide = isCollideSphereAndSphere( collider1, collider2 );

				if ( collide ) {
					collider1->onColliderEnter( collider2 );
					collider2->onColliderEnter( collider1 );
				}
			}
		}

		{ // sphere → square
			for ( int i = 0; i < _static_square_obj.size( ); i++ ) {
				SphereColliderPtr collider1 = ( *ite ).lock( );
				SquareColliderPtr collider2 = _static_square_obj[ i ];

				if ( !collider1 ) {
					break;
				}

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
	if ( !collider1->isEnabled( ) || !collider2->isEnabled( ) ) {
		return false;
	}

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
	if ( !collider1->isEnabled( ) || !collider2->isEnabled( ) ) {
		return false;
	}

	Vector sphere_pos = collider1->getPos( );
	double radius = collider1->getRadius( );

	Vector square_center_pos = collider2->getPos( );
	Vector norm = collider2->getNorm( );
	double width = collider2->getWidth( );
	double height = collider2->getHeight( );

	// 面を横から見た時に球が重なっているかを判定
	double dot = norm.dot( sphere_pos - square_center_pos );
	if ( fabs( dot ) > radius ) {
		return false;
	}

	// 面の座標の割り出し
	Vector horizontal = norm.cross( Vector( norm.x, norm.y + 100, norm.z ) ).normalize( ); // 横
	Vector vertical = norm.cross( horizontal ).normalize( ); // 縦

	// 回転するようにする
	Vector square_pos[ 4 ] = {
		square_center_pos + ( horizontal * -1 * width * 0.5 ) + ( vertical *  1 * height * 0.5 ),
		square_center_pos + ( horizontal *  1 * width * 0.5 ) + ( vertical *  1 * height * 0.5 ),
		square_center_pos + ( horizontal *  1 * width * 0.5 ) + ( vertical * -1 * height * 0.5 ),
		square_center_pos + ( horizontal * -1 * width * 0.5 ) + ( vertical * -1 * height * 0.5 ),
	};

	// 面の中に球があるかどうか
	int past_dot = 999; // -1 or 1 を格納, 999は適当な初期値
	for ( int i = 0; i < 4; i++ ) {
		Vector vertex1 = square_pos[ ( i + 0 ) % 4 ];
		Vector vertex2 = square_pos[ ( i + 1 ) % 4 ];

		// line1, line2 で三角形を作成
		Vector line1 = ( vertex2 - vertex1 );  
		Vector line2 = line1 + norm * 100 * -1;
		Vector cross = line1.cross( line2 ).normalize( ); // 作成した三角形の垂線

		Vector line3 = sphere_pos - vertex1;
		// 正射影(方向のみ)
		int dot = ( cross.dot( line3 ) < 0 ? -1 : 1 );

		// 方向が違うものがあれば内側にない
		if ( past_dot != 999 && dot != past_dot ) {
			return false;
		}
		past_dot = dot;
	}

	return true;
}