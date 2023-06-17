#include "Bullet.h"
#include "ObjectManager.h"	
#include "AssetManager.h"
#include "HUDCamera.h"

Bullet::Bullet(ObjectTag userTag) :
	ObjectBase(ObjectTag::Bullet)
{
	// �A�Z�b�g�}�l�[�W���[���烂�f�������[�h.
	modelHandle = AssetManager::GetMesh("data/beam.mv1");
	MV1SetScale(modelHandle, VGet(modelScale, modelScale, modelScale));// �T�C�Y�̕ύX.
	myTag = userTag;
	Init();
	// �����蔻�苅�Z�b�g.
	colType = CollisionType::Sphere;
	colSphere.worldCenter = pos;
	colSphere.radius = ColRadius;
	CollisionUpdate();

}

Bullet::~Bullet()
{
	AssetManager::DeleteMesh(modelHandle);
	alive = false;
}

void Bullet::Init()
{
	// �ϐ��̏�����.
	visible = false;
	permitUpdate = false;
	this->dir = this->pos = velocity = InitVec;
	timeCount = DeadTime;
	CollisionUpdate();
}

void Bullet::Update(float deltaTime)
{
	�@�̂̏d�͂��m�F�@�^�[�Q�b�g�T�[�N���̒��ɒe��͈͂ɓ����
	Delete();

	velocity = ToZAxis(matRot) * -Speed * deltaTime;
	velocity.y -= G;
	prePos += velocity;
	CollisionUpdate(prePos);
	pos = prePos;
	// �ʒu�̍X�V.
	/*MV1SetPosition(modelHandle, pos);
	MV1SetRotationZYAxis(modelHandle, dir, VGet(0.0f, 1.0f, 0.0f), 0.0f);*/
	mat = MGetScale(VGet(modelScale, modelScale, modelScale));
	mat = mat * matRot;
	mat = mat * MGetTranslate(pos);
	MV1SetMatrix(modelHandle, mat);

	timeCount -= deltaTime;
	if (timeCount <= 0)
	{
		Init();
	}
}

void Bullet::Generate(int ModelHandle, int frameIndex, MATRIX matDir)
{
	matTrans = MV1GetFrameLocalWorldMatrix(ModelHandle, frameIndex);
	matRot = MGetRotAxis(ToYAxis(matDir), ToRadian(ZeroInAngle));
	pos = M2Pos(matTrans);
	prePos = pos;
	timeCount = DeadTime;
	visible = true;
	permitUpdate = true;
	CollisionUpdate();
	mat = MGetScale(VGet(modelScale, modelScale, modelScale));
	mat = mat * matRot;

	mat = mat * matTrans;
	MV1SetMatrix(modelHandle, mat);
	//MV1SetPosition(modelHandle, this->pos);
	//MV1SetRotationZYAxis(modelHandle, this->dir, VGet(0.0f, 1.0f, 0.0f), 0.0f);
}


void Bullet::Draw()
{
	MV1DrawModel(modelHandle);
	int white = GetColor(255, 255, 255);
	DrawFormatString(0, 60, white, "%f,%f,%f", dir.x, dir.y, dir.z);

	DrawCollider();
}

float Bullet::CalculateAngle(VECTOR airplanePos, MATRIX airplaneMatDir)
{
	float a = VSize(airplanePos - this->pos);
	float b = VSize((airplanePos + (ToZAxis(airplaneMatDir) * GunTargetingDistance)) - this->pos);
	float molecule = (GunTargetingDistance * GunTargetingDistance) + (b * b) - (a - a);
	float denominator = 2.0f * GunTargetingDistance * b;
	return molecule / denominator;
}

void Bullet::Delete()
{
	if (pos.y <= 0)
	{
		visible = false;
		permitUpdate = false;
	}
	if (prePos.y <= 0)
	{
		pos.y = 0;
	}
}

void Bullet::OnCollisionEnter(const ObjectBase* other)
{
}