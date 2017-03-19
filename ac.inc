/**
*
*	Regasen Play
*	Античит
*	ac_status(playerid) - Статус античита для игрока (1 - Включен/2 - Выключен)
* 	ac_switch(playerid) - Меняет статус античита для игрока
*
**/
#define ANTICHEAT_CODE_AIRBREAK (1)
#define ANTICHEAT_CODE_SPECTATE (2)
#define ANTICHEAT_CODE_HP 		(3)
#define ANTICHEAT_CODE_WEAPON 	(4)
#define ANTICHEAT_CODE_ARMOUR 	(5)

forward OnCheatDetected(playerid, code);
forward ac_timer(playerid);

new 
	ac_timer_var[MAX_PLAYERS],
	ac_ignore[MAX_PLAYERS];

public ac_timer(playerid)
{
	if(!ac_ignore[playerid]) return false;
    #if defined ac_inc_timer
        return ac_inc_timer(playerid);
    #else
        return 1;
    #endif
}
#if defined _ALS_ac_timer
    #undef ac_timer
#else
    #define _ALS_ac_timer
#endif

#define ac_timer ac_inc_timer
#if defined ac_inc_timer
    forward ac_inc_timer(playerid);
#endif

#include "../source/anticheat/hp.inc"
#include "../source/anticheat/fly.inc"
#include "../source/anticheat/spec.inc"
#include "../source/anticheat/weapon.inc"
#include "../source/anticheat/armour.inc"

stock ac_switch(playerid)
{
	ac_ignore[playerid] = (ac_ignore[playerid] ? 0 : 1);
	SetPVarInt(playerid, "ac-ignore", gettime() + 1);
}

stock ac_status(playerid)
{
	return ac_ignore[playerid];
}

public OnCheatDetected(playerid, code)
{
	static const _msg[] = "Обнаружено использование программы, дающие нечестное преимущество в игре: «{FFA500}%s{FFFFFF}»";
	switch(code)
	{
	    case ANTICHEAT_CODE_AIRBREAK:
	    {
	        SendFormattedMessage(playerid, -1, _msg, "Телепортация/Полет");
	    }
	    case ANTICHEAT_CODE_SPECTATE:
	    {
	        SendFormattedMessage(playerid, -1, _msg, "Невидимка");
	    }
	    case ANTICHEAT_CODE_HP:
	    {
	        SendFormattedMessage(playerid, -1, _msg, "Пополнение жизни");
	    }
	    case ANTICHEAT_CODE_WEAPON:
	    {
	        SendFormattedMessage(playerid, -1, _msg, "Добавление патронов/Получение оружия");
	    }
	    case ANTICHEAT_CODE_ARMOUR:
	    {
	        SendFormattedMessage(playerid, -1, _msg, "Пополнение брони");
	    }
	}
	Kick(playerid);
	return true;
}

public OnPlayerSpawn(playerid)
{
	SetPVarInt(playerid, "ac-ignore", gettime() + 1);
	
    #if defined ac_OnPlayerSpawn
        return ac_OnPlayerSpawn(playerid);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnPlayerSpawn
    #undef OnPlayerSpawn
#else
    #define _ALS_OnPlayerSpawn
#endif

#define OnPlayerSpawn ac_OnPlayerSpawn
#if defined ac_OnPlayerSpawn
    forward ac_OnPlayerSpawn(playerid);
#endif

public OnPlayerConnect(playerid)
{
	ac_switch(playerid);
	
	SetPVarInt(playerid, "ac-ignore", gettime() + 1000);
	ac_timer_var[playerid] = SetTimerEx("ac_timer", 1000, true, "d", playerid);
	
    #if defined ac_OnPlayerConnect
        return ac_OnPlayerConnect(playerid);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnPlayerConnect
    #undef OnPlayerConnect
#else
    #define _ALS_OnPlayerConnect
#endif

#define OnPlayerConnect ac_OnPlayerConnect
#if defined ac_OnPlayerConnect
    forward ac_OnPlayerConnect(playerid);
#endif

public OnPlayerDisconnect(playerid, reason)
{
	ac_switch(playerid);
	KillTimer(ac_timer_var[playerid]);
	
    #if defined ac_OnPlayerConnect
        return ac_OnPlayerConnect(playerid);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnPlayerDisconnect
    #undef OnPlayerDisconnect
#else
    #define _ALS_OnPlayerDisconnect
#endif

#define OnPlayerDisconnect ac_OnPlayerDisconnect
#if defined ac_OnPlayerDisconnect
    forward ac_OnPlayerDisconnect(playerid, reason);
#endif