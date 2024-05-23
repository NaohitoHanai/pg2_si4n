#include "GoblinAI.h"
#include "Goblin.h"
#include "../Library/GameObject.h"
#include "Player.h"
#include "../Library/Time.h"
#include "../ImGui/imgui.h"

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

Node::~Node()
{
    for (Node* c : children) {
        delete c;
    }
    children.clear();
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
    // ゴブリンの座標
    Goblin* pObj = dynamic_cast<Goblin*>(object);
    VECTOR gPos = pObj->Position();
    // プレイヤーの座標
    Player* pPl = ObjectManager::FindGameObject<Player>();
    VECTOR pPos = pPl->Position();
    if (VSquareSize(gPos - pPos) < 200 * 200) {
        // プレイヤーが攻撃している
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
        // ゴブリンの逃げるベクトル
        // ゴブリンの座標
        Goblin* pObj = dynamic_cast<Goblin*>(object);
        VECTOR gPos = pObj->Position();
        // プレイヤーの座標
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
    // よけの行動が終わったらtrue
    return false;
}

bool GoblinAttack::NeedEnable()
{
    // プレイヤーが400より近ければtrue
    // ゴブリンの座標
    Goblin* pObj = dynamic_cast<Goblin*>(object);
    VECTOR gPos = pObj->Position();
    // プレイヤーの座標
    Player* pPl = ObjectManager::FindGameObject<Player>();
    VECTOR pPos = pPl->Position();
    if (VSquareSize(gPos - pPos) < 400 * 400) {
        timer = 0;
        return true;
    }
    return false;
}

bool GoblinAttack::Update()
{
    Goblin* pObj = dynamic_cast<Goblin*>(object);
    if (timer == 0) {
        pObj->AddPosition(VGet(0, 150, 0));
    }
    timer += Time::DeltaTime();
    if (timer >= 1.0f) {
        pObj->AddPosition(VGet(0, -150, 0));
        return true;
    }
    // 攻撃の行動が終わったらtrue
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
    // childrenを順番に見て、NeedEnableのものがあればtrue
//    for (std::list<Node*>::iterator itr = children.begin(); itr != children.end(); itr++) {
//        Node* c = *itr;
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
    // 今選んでいるものを実行し、終わったらtrue
    if (selected == nullptr || selected->Update()) {
        if (NeedEnable()) {
            return false;
        }
        selected = nullptr;
        return true;
    }
    return false;
}

Sequencer::Sequencer(GameObject* obj) : Node(obj)
{
    children.push_back(new GoblinAvoid(obj));
    children.push_back(new GoblinAttack(obj));
    itr = children.begin();
}

bool Sequencer::NeedEnable()
{
    for (; itr != children.end(); itr++) {
        Node* c = *itr;
        if (c->NeedEnable()) {
            return true;
        }
    }
    return false;
}

bool Sequencer::Update()
{
    // 今選んでいるものを実行し、終わったらtrue
    if (itr == children.end())
    {
        itr = children.begin();
    }
    if ((*itr)->Update()) {
        itr++;
        if (NeedEnable()) {
            return false;
        }
        return true;
    }
    return false;
}
