#ifndef STATEMACHINE_H 
#define STATEMACHINE_H
#include "state_common.h"
#include "enemy.h"
#include "line.h"
#include "timer.h"
#include "drive.h"
#include "drivers/ir_remote.h"
#include "common/defines.h"

// -------- Enums and Structs -------- //
typedef struct {
    state_e from_state;
    state_event_e event; 
    state_e to_state;
} state_transition_s;

// ------- Forward Declarations ------ //
class StateWait;
class StateSearch;
class StateAttack;
class StateRetreat;
class StateManual;

// ---- Abstract State Interface ----- //
class StateBase {
public:
    virtual void enter(state_e from, state_event_e event) = 0;
    virtual void run() = 0;
    virtual void init() = 0;
    virtual ~StateBase() = default;
};

// ------- State Machine Class ------- //
class StateMachine {
public:
    explicit StateMachine();

    void init();
    void run();
    state_event_e processInput();
    void processEvent(state_event_e event);
    void stateEnter(state_e from, state_event_e event, state_e to);

    void postInternalEvent(state_event_e e);
    bool hasInternalEvent() const;
    state_event_e takeInternalEvent();

    state_e getCurrentState() const { return currentState; }
    timer_t* getTimer() { return timer; }
    ir_command_e getCommand() const { return command; }
    enemy_pos_e getEnemy() { return enemy; }
    line_pos_e getLine() { return line; }

private:
    state_e currentState;
    state_event_e internalEvent;

    // states
    StateWait* waitState;
    StateSearch* searchState;
    StateAttack* attackState;
    StateRetreat* retreatState;
    StateManual* manualState;

    // other
    state_event_e internal_event;
    timer_t *timer;

    // common data
    enemy_pos_e enemy;
    line_pos_e line;
    ir_command_e command;

    static constexpr int NUM_TRANSITIONS = 24;
    static const state_transition_s transitions[NUM_TRANSITIONS];
};

// ----- Concrete State Classes ----- //

// ------- WAIT STATE ------- // 
class StateWait : public StateBase {
public:
    explicit StateWait(StateMachine* sm);
    void enter(state_e from, state_event_e event) override;
    void run() override;
    void init() override;

private:
    StateMachine* stateMachine;
};

// ------ SEARCH STATE ------- // 
class StateSearch : public StateBase {
public:
    enum class InternalSearchState {
        ROTATE,
        FORWARD
    };

    explicit StateSearch(StateMachine* sm);
    void enter(state_e from, state_event_e event) override;
    void run() override;
    void init() override;

private:
    StateMachine* stateMachine;
    InternalSearchState internalState;
};

// ------ ATTACK STATE ------- // 
class StateAttack : public StateBase {
public:
    enum class InternalAttackState {
        FORWARD,
        LEFT,
        RIGHT
    };

    explicit StateAttack(StateMachine* sm);
    void enter(state_e from, state_event_e event) override;
    void run() override;
    void init() override;

private:
    StateMachine* stateMachine;
    InternalAttackState internalState;
    InternalAttackState nextAttackState(enemy_pos_e enemy);
};

// ------ RETREAT STATE ------- // 
class StateRetreat : public StateBase {
public:
    enum class InternalRetreatState {
        REVERSE,
        FORWARD,
        ROTATE_LEFT,
        ROTATE_RIGHT,
        ARCTURN_LEFT,
        ARCTURN_RIGHT,
        ALIGN_LEFT,
        ALIGN_RIGHT
    };
    struct Move {
        drive_dir_e direction;
        drive_speed_e speed;
        uint16_t duration;
    };
    struct RetreatMove {
        const Move* moves;
        uint8_t moveCount;
    };
    explicit StateRetreat(StateMachine* sm);
    void enter(state_e from, state_event_e event) override;
    void run() override;
    void init() override;

private:
    StateMachine* stateMachine;
    InternalRetreatState internalState;      
    int moveIndex;                             

    void stateRetreatRun();                    
    void startRetreatMove();                   
    bool retreatStateDone() const;             
    Move currentMove() const;                
    InternalRetreatState nextRetreatState() const; 

    static const RetreatMove retreatStates[]; 
};

// ------ MANUAL STATE ------- //
class StateManual : public StateBase {
public:
    explicit StateManual(StateMachine* sm);
    void enter(state_e from, state_event_e event) override;
    void run() override;
    void init() override;

private:
    StateMachine* stateMachine;
};

#endif 