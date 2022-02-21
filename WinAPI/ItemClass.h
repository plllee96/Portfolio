#pragma once
#include "Stdafx.h"

enum class EITEM_TYPE
{
	ENPTY=0,
	EQUIP_WEAPOEN_BOW,
	EQUIP_WEAPOEN_SWORD,
	EQUIP_ARMOR,
	EQUIP_HAT,
	EQUIP_SHOES,
	STAT,
	MATERIAL,
	SCROLL,
};

class CPlayer_Attribute
{
public:
	int	  _hp;				//hp
	int   _maxHp;			//maxhp
	int   _mana;			//mana
	int   _maxMana;			//maxMana
	float _critical;		//ũ��Ȯ��
	float _offencePower;	//���ݷ�
	float _magicPower;		//������
	float _speed;			//�̵��ӵ�
	float _attackSpeed;		//���ݼӵ�
	float _damageBalace;	//������ �뷱��
	float _experience;		//����ġ
	float _stamina;			//���׹̳�

	CPlayer_Attribute operator+(CPlayer_Attribute other)
	{
		CPlayer_Attribute temp;
		temp._hp = _hp + other._hp;
		temp._maxHp = _maxHp + other._maxHp;
		temp._mana = _mana + other._mana;
		temp._maxMana = _maxMana + other._maxMana;
		temp._critical = _critical + other._critical;
		temp._offencePower = _offencePower + other._offencePower;
		temp._magicPower = _magicPower + other._magicPower;
		temp._speed = _speed + other._speed;
		temp._attackSpeed = _attackSpeed + other._attackSpeed;
		temp._damageBalace = _damageBalace + other._damageBalace;
		temp._experience = _experience + other._experience;
		temp._stamina = _stamina + other._stamina;
		return temp;
	}

	void operator=(CPlayer_Attribute other)
	{
		_hp + other._hp;
		_maxHp + other._maxHp;
		_mana + other._mana;
		_maxMana + other._maxMana;
		_critical + other._critical;
		_offencePower + other._offencePower;
		_magicPower + other._magicPower;
		_speed + other._speed;
		_attackSpeed + other._attackSpeed;
		_damageBalace + other._damageBalace;
		_experience + other._experience;
		_stamina + other._stamina;
	}

	CPlayer_Attribute()
	{
		_hp = 0;
		_maxHp = 0;
		_mana = 0;
		_maxMana = 0;
		_critical = 0.0f;
		_offencePower = 0.0f;
		_magicPower = 0.0f;
		_speed = 0.0f;
		_attackSpeed = 0.0f;
		_damageBalace = 0.0f;
		_experience = 0.0f;
		_stamina = 0.0f;
	}
	~CPlayer_Attribute() {}
};


class Item
{
public:
	int _index;
	EITEM_TYPE _type;				//������ Ÿ��
	string _name;					//name
	string _description;			//����
	int _imgNum;					//��� �̹��� �ѹ�
	int _equip_level;				//��� ����
	int _price;						//����

	CPlayer_Attribute _attribute;	//�ɷ�ġ

	inline void setItemData(int index,EITEM_TYPE type, string name, string description, int imgNum, int equip_level, int price)
	{
		_index = index;
		_type = type;
		_name= name;
		_description= description;
		_imgNum = imgNum;
		_equip_level= equip_level;
		_price = price;
	}
	inline void setItemAttribute(int   hp,
								 int   maxHp,
								 int   mana,
								 int   maxMana,
								 float critical,
								 float offencePower,
								 float magicPower,
								 float speed,
								 float attackSpeed,
								 float damageBalace,
								 float experience,
								 float stamina)
	{
		_attribute._hp = hp;
		_attribute._maxHp =maxHp;
		_attribute._mana =mana;
		_attribute._maxMana =maxMana;
		_attribute._critical =critical;
		_attribute._offencePower =offencePower;
		_attribute._magicPower =magicPower;
		_attribute._speed =speed;
		_attribute._attackSpeed =attackSpeed;
		_attribute._damageBalace =damageBalace;
		_attribute._experience =experience;
		_attribute._stamina = stamina;
	}

	Item()
	{
		_type = EITEM_TYPE::ENPTY;
		_name = "ENPTY";
		_description = "ENPTY";
		_imgNum = 0;
		_equip_level = 0;
		_price = 0;
	}
	~Item() {}
};

class Player_Skill : public IRectObserved
{
public:
	my::Image* _img;
	RECT rc;
	string _name;
	float _damage;
	float _range;
	ObservedType _type;
	bool _isActive;
	
	void init(void);
	void release(void);
	virtual STObservedData getRectUpdate();
	virtual void collideObject();

};