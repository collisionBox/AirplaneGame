#include "Bullet.h"
#include "ObjectManager.h"	
#include "AssetManager.h"


Bullet::Bullet(VECTOR pos, VECTOR dir, ObjectTag userTag) :
	ObjectBase(ObjectTag::Bullet)
{
	// �A�Z�b�g�}�l�[�W���[���烂�f�������[�h.
	modelHandle = AssetManager::GetMesh("data/beam.mv1");
	MV1SetScale(modelHandle, VGet(0.1f, 0.1f, 0.08f));// �T�C�Y�̕ύX.
	// �ʒu�E������������.
	this->pos = pos;
	this->dir = dir;
	this->pos = VAdd(this->pos ,VScale(this->dir, barrelHead));// �C���擪�ɃZ�b�g���邽��.

	MV1SetPosition(modelHandle, this->pos);
	MV1SetRotationZYAxis(modelHandle, this->dir, VGet(0.0f, 1.0f, 0.0f), 0.0f);

	// �����蔻�苅�Z�b�g.
	colType = CollisionType::Sphere;
	colSphere.worldCenter = pos;
	colSphere.radius = colRadius;
	CollisionUpdate();
	// �ϐ��̏�����.
	velocity = InitVec;
	reflectionFlag = false;
	myTag = userTag;


}

Bullet::~Bullet()
{
	AssetManager::DeleteMesh(modelHandle);

}

void Bullet::Update(float deltaTime)
{
	velocity = VScale(VScale(dir, speed), deltaTime);
	prevPos = VAdd(pos, velocity);

	if (offscreenDicision(pos))
	{
		SetVisible(false);
	}

	CollisionUpdate(prevPos);

	pos = prevPos;
	// �ʒu�̍X�V.
	MV1SetPosition(modelHandle, pos);
	MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI_F / 180.0f));
	VECTOR negativeVec = VTransform(dir, rotYMat);
	MV1SetRotationZYAxis(modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);

}


void Bullet::Draw()
{
	MV1DrawModel(modelHandle);
	DrawCollider();
	
}

void Bullet::OnCollisionEnter(const ObjectBase* other)
{
}