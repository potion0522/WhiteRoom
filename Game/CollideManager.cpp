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
		{ // sphere �� sphere
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

		{ // sphere �� sphere
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

		{ // sphere �� square
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

	// �ʂ������猩�����ɋ����d�Ȃ��Ă��邩�𔻒�
	double dot = norm.dot( sphere_pos - square_center_pos );
	if ( fabs( dot ) > radius ) {
		return false;
	}

	// �ʂ̍��W�̊���o��
	Vector horizontal = norm.cross( Vector( norm.x, norm.y + 100, norm.z ) ).normalize( ); // ��
	Vector vertical = norm.cross( horizontal ).normalize( ); // �c

	// ��]����悤�ɂ���
	Vector square_pos[ 4 ] = {
		square_center_pos + ( horizontal * -1 * width * 0.5 ) + ( vertical *  1 * height * 0.5 ),
		square_center_pos + ( horizontal *  1 * width * 0.5 ) + ( vertical *  1 * height * 0.5 ),
		square_center_pos + ( horizontal *  1 * width * 0.5 ) + ( vertical * -1 * height * 0.5 ),
		square_center_pos + ( horizontal * -1 * width * 0.5 ) + ( vertical * -1 * height * 0.5 ),
	};

	// �ʂ̒��ɋ������邩�ǂ���
	int past_dot = 999; // -1 or 1 ���i�[, 999�͓K���ȏ����l
	for ( int i = 0; i < 4; i++ ) {
		Vector vertex1 = square_pos[ ( i + 0 ) % 4 ];
		Vector vertex2 = square_pos[ ( i + 1 ) % 4 ];

		// line1, line2 �ŎO�p�`���쐬
		Vector line1 = ( vertex2 - vertex1 );  
		Vector line2 = line1 + norm * 100 * -1;
		Vector cross = line1.cross( line2 ).normalize( ); // �쐬�����O�p�`�̐���

		Vector line3 = sphere_pos - vertex1;
		// ���ˉe(�����̂�)
		int dot = ( cross.dot( line3 ) < 0 ? -1 : 1 );

		// �������Ⴄ���̂�����Γ����ɂȂ�
		if ( past_dot != 999 && dot != past_dot ) {
			return false;
		}
		past_dot = dot;
	}

	return true;
}