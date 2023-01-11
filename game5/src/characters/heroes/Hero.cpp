//
// Created by colte on 26.12.2022.
//

#include "Hero.h"
#include "../items.h"

Hero::Hero()
{
    nA = "";
    hA = "";
    sp = "";
    maxHP = 0;
    hp = 0;
    block = 0;
    evasion = 0;
    buffsDur = 0;
    minNDMG = 0;
    minHDMG = 0;
    spValue = 0;
    gold = 0;
    mcN = 0;
    mcH = 0;
    ability = nullptr;
    charType = 0;
    slotN = 2;
    items = {
            new Healing(0),
            new Healing(0)
    };
    for(auto& el: items)
    {
        el->setName("Empty slot");
        el->setNum(0);
    }
}

Hero::~Hero()
{
    if (ability != nullptr)
    {
        delete ability;
        ability = nullptr;
    }
    for(auto& el: items)
        delete el;
    items.clear();
}

void Hero::setItem(Item* it)
{
    short sl = findFreeSlot();
    if (sl != slotN)
    {
        clearSlot(sl);
        items[sl] = it;
    }
}

void Hero::useItem(GameplayData& gd, short i)
{
    items[i]->activate(gd);
    clearSlot(i);
}

void Hero::clearSlot(short i)
{
    delete items[i];
    items[i] = nullptr;
    items[i] = new Healing(1);
    items[i]->setName("Empty slot");
    items[i]->setVal(0);
    items[i]->setNum(0);
}

short Hero::findFreeSlot()
{
    short result = 0;
    for(auto& el: items)
    {
        if(el->getNum() == 0)
            break;
        result++;
    }
    return result;
}

void Hero::GetData(GameplayData &gd) {
    if(ability != nullptr)
        gd.hero.numOfAb = ability->numOfAb;
    else gd.hero.numOfAb = 0;
    gd.hero.charType = charType;
}

void Hero::SetData(GameplayData &gd) {
    maxHP += gd.hero.maxHP;
    if(gd.hero.hp < 0)
    {
        gd.hero.block += gd.hero.hp;
        if(gd.hero.block < 0)
        {
            block += gd.hero.block;
            if(block < 0)
            {
                gd.hero.hp = block;
                hp += block;
                if(hp < 0) hp = 0;
            }
        }
        if(gd.hero.block < 0)
            gd.hero.block = 0;
        if(block < 0)
            block = 0;
        else gd.hero.hp = 0;
    }
    else hp += gd.hero.hp;
    if(hp > maxHP) hp = maxHP;
    if(gd.hero.block > 0) block += gd.hero.block;
    evasion += gd.hero.evasion;
    buffsDur += gd.hero.buffDur;
    ability->statusDur += gd.hero.statusDur;
    ability->curDelay += gd.hero.curDel;
}

void Hero::SetData(RewardStats &rs) {
    gold += rs.gold;
    maxHP += rs.hp;
    minNDMG += rs.nDMG;
    minHDMG += rs.hDMG;
    spValue += rs.spVal;
    evasion += rs.evasion;
}
