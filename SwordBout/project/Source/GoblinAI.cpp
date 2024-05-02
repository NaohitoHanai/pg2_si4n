#include "GoblinAI.h"
#include "Goblin.h"

GoblinAI::GoblinAI(Goblin* p)
{
    parent = p;
    rootNode = new Selector();
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
    return false;
}

bool GoblinAvoid::Update()
{
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

Selector::Selector()
{
    children.push_back(new GoblinAvoid());
    children.push_back(new GoblinAttack());
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
    return false;
}

bool Selector::Update()
{
    // ���I��ł�����̂����s���A�I�������true
    if (selected == nullptr || selected->Update()) {
        if (NeedEnable()) {
            return false;
        }
        return true;
    }
    return false;
}







