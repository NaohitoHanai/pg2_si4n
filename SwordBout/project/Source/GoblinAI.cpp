#include "GoblinAI.h"
#include "Goblin.h"
#include "../Library/GameObject.h"
#include "Player.h"
#include "../Library/Time.h"

GoblinAI::GoblinAI(Goblin* p)
{
    parent = p;
    rootNode = new Selector(parent);
}
GoblinAI::~GoblinAI()
{
}
void GoblinAI::Update()
{
    rootNode->Update();
}

bool Node::NeedEnable()
{
    return false;
}

bool Node::Update()
{
    return false;
}

bool GoblinAvoid::NeedEnable()
{
    // �v���C���[���߂��ōU��������true
    // �S�u�����̍��W
    Goblin* pObj = dynamic_cast<Goblin*>(object);
    VECTOR gPos = pObj->Position();
    // �v���C���[�̍��W
    Player* pPl = ObjectManager::FindGameObject<Player>();
    VECTOR pPos = pPl->Position();
    if (VSquareSize(gPos - pPos) < 200 * 200) {
        // �v���C���[���U�����Ă���
        if (pPl->Attacking()) {
            timer = 0;
            return true;
        }
    }
    return false;
}

bool GoblinAvoid::Update()
{
    if (timer == 0) {
        // �S�u�����̓�����x�N�g��
        // �S�u�����̍��W
        Goblin* pObj = dynamic_cast<Goblin*>(object);
        VECTOR gPos = pObj->Position();
        // �v���C���[�̍��W
        Player* pPl = ObjectManager::FindGameObject<Player>();
        VECTOR pPos = pPl->Position();
        VECTOR AvoidVec = gPos - pPos;
        //    AvoidVec = AvoidVec * (100.0f / VSize(AvoidVec));
        AvoidVec = VNorm(AvoidVec) * 100.0f;
        pObj->AddPosition(AvoidVec);
    }
    timer += Time::DeltaTime();
    if (timer >= 1.0f)
        return true;
    // �悯�̍s�����I�������true
    return false;
}

bool GoblinAttack::NeedEnable()
{
    // �v���C���[���߂����
    return false;
}

bool GoblinAttack::Update()
{
    // �U���̍s�����I�������true
    return false;
}

Selector::Selector(GameObject* obj) : Node(obj)
{
    children.push_back(new GoblinAvoid(obj));
    children.push_back(new GoblinAttack(obj));
    selected = nullptr;
}

bool Selector::NeedEnable()
{
    // children�����ԂɌ��āANeedEnable�̂��̂������true
    for (Node* c : children) {
        if (c->NeedEnable()) {
            selected = c;
            return true;
        }
    }
    selected = nullptr;
    return false;
}

bool Selector::Update()
{
    // ���I��ł�����̂����s���A�I�������true
    if (selected == nullptr || selected->Update()) {
        if (NeedEnable()) {
            return false;
        }
        selected = nullptr;
        return true;
    }
    return false;
}







