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
    // プレイヤーが近くで攻撃したらtrue
    return false;
}

bool GoblinAvoid::Update()
{
    // よけの行動が終わったらtrue
    return false;
}

bool GoblinAttack::NeedEnable()
{
    // プレイヤーが近ければ
    return false;
}

bool GoblinAttack::Update()
{
    // 攻撃の行動が終わったらtrue
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
    // childrenを順番に見て、NeedEnableのものがあればtrue
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
    // 今選んでいるものを実行し、終わったらtrue
    if (selected == nullptr || selected->Update()) {
        if (NeedEnable()) {
            return false;
        }
        return true;
    }
    return false;
}







