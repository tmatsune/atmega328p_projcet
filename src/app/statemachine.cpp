#include "statemachine.h"
#include "common/assert_handler.h"

void print_state(state_e state)
{
    if (state == STATE_WAIT) Serial.println("WAIT");
    else if (state == STATE_SEARCH) Serial.println("SRCH");
    else if (state == STATE_ATTACK) Serial.println("ATK");
    else if (state == STATE_RETREAT) Serial.println("RETREAT");
    else if (state == STATE_MANUAL) Serial.println("MANUAL");
}


void print_event(state_event_e event)
{
    if (event == STATE_EVENT_TIMEOUT) Serial.println("TIMEOUT");
    else if (event == STATE_EVENT_LINE) Serial.println("LINE");
    else if (event == STATE_EVENT_ENEMY) Serial.println("ENEMY");
    else if (event == STATE_EVENT_FINISHED) Serial.println("FINISHED");
    else if (event == STATE_EVENT_COMMAND) Serial.println("CMD");
    else if (event == STATE_EVENT_NONE) Serial.println("NONE");
}

// Define state transitions
const state_transition_s StateMachine::transitions[NUM_TRANSITIONS] = {
    {STATE_WAIT, STATE_EVENT_NONE,    STATE_WAIT},
    {STATE_WAIT, STATE_EVENT_LINE,    STATE_WAIT},
    {STATE_WAIT, STATE_EVENT_ENEMY,   STATE_WAIT},
    {STATE_WAIT, STATE_EVENT_COMMAND, STATE_SEARCH},

    {STATE_SEARCH, STATE_EVENT_NONE,    STATE_SEARCH},
    {STATE_SEARCH, STATE_EVENT_TIMEOUT, STATE_SEARCH},
    {STATE_SEARCH, STATE_EVENT_ENEMY,   STATE_ATTACK},
    {STATE_SEARCH, STATE_EVENT_LINE,    STATE_RETREAT},
    {STATE_SEARCH, STATE_EVENT_COMMAND, STATE_MANUAL},

    {STATE_ATTACK, STATE_EVENT_ENEMY,   STATE_ATTACK},
    {STATE_ATTACK, STATE_EVENT_LINE,    STATE_RETREAT},
    {STATE_ATTACK, STATE_EVENT_NONE,    STATE_SEARCH},
    {STATE_ATTACK, STATE_EVENT_COMMAND, STATE_MANUAL},
    {STATE_ATTACK, STATE_EVENT_TIMEOUT, STATE_ATTACK},

    {STATE_RETREAT, STATE_EVENT_LINE,     STATE_RETREAT},
    {STATE_RETREAT, STATE_EVENT_FINISHED, STATE_SEARCH},
    {STATE_RETREAT, STATE_EVENT_TIMEOUT,  STATE_RETREAT},
    {STATE_RETREAT, STATE_EVENT_ENEMY,    STATE_RETREAT},
    {STATE_RETREAT, STATE_EVENT_NONE,     STATE_RETREAT},
    {STATE_RETREAT, STATE_EVENT_COMMAND,  STATE_MANUAL},

    {STATE_MANUAL, STATE_EVENT_COMMAND, STATE_MANUAL},
    {STATE_MANUAL, STATE_EVENT_NONE,    STATE_MANUAL},
    {STATE_MANUAL, STATE_EVENT_LINE,    STATE_MANUAL},
    {STATE_MANUAL, STATE_EVENT_ENEMY,   STATE_MANUAL},
};

// --------------------- StateMachine ------------------------
StateMachine::StateMachine()
    : currentState(STATE_WAIT), internalEvent(STATE_EVENT_NONE),
      timer(), enemy(ENEMY_POS_NONE), line(LINE_NONE), command(CMD_NONE) {
    waitState = new StateWait(this);
    searchState = new StateSearch(this);
    attackState = new StateAttack(this);
    retreatState = new StateRetreat(this);
    manualState = new StateManual(this);
    timer = new timer_t;
}

void StateMachine::init() {
    waitState->init();
    searchState->init();
    attackState->init();
    retreatState->init();
    manualState->init();
    timer_clear(timer);
    internalEvent = STATE_EVENT_NONE;
    currentState = STATE_WAIT;
    enemy = ENEMY_POS_NONE;
    line = LINE_NONE;
    command = CMD_NONE;
    Serial.println("init SM");
}

void StateMachine::run() {
    state_event_e event = processInput();
    processEvent(event);
    print_state(this->currentState);
}

state_event_e StateMachine::processInput() {
    line = get_line_pos();
    enemy = get_enemy_pos();
    command = get_ir_command();

    if (command != CMD_NONE) return STATE_EVENT_COMMAND;
    if (hasInternalEvent()) return takeInternalEvent();
    if (timer_timeout(this->timer)) return STATE_EVENT_TIMEOUT;
    if (line != LINE_NONE) return STATE_EVENT_LINE;
    if (enemy != ENEMY_POS_NONE) return STATE_EVENT_ENEMY;
    return STATE_EVENT_NONE;
}

void StateMachine::processEvent(state_event_e event) {
    for (int i = 0; i < NUM_TRANSITIONS; ++i) {
        if (transitions[i].from_state == currentState && transitions[i].event == event) {
            stateEnter(transitions[i].from_state, event, transitions[i].to_state);
            return;
        }
    }
}

void StateMachine::stateEnter(state_e from, state_event_e event, state_e to) {
    if (from != to) {
        timer_clear(this->timer);
        currentState = to;
    }
    switch (to) {
        case STATE_WAIT: waitState->enter(from, event); break;
        case STATE_SEARCH: searchState->enter(from, event); break;
        case STATE_ATTACK: attackState->enter(from, event); break;
        case STATE_RETREAT: retreatState->enter(from, event); break;
        case STATE_MANUAL: manualState->enter(from, event); break;
    }
}

bool StateMachine::hasInternalEvent() const {
    return internalEvent != STATE_EVENT_NONE;
}

state_event_e StateMachine::takeInternalEvent() {
    state_event_e e = internalEvent;
    internalEvent = STATE_EVENT_NONE;
    return e;
}

void StateMachine::postInternalEvent(state_event_e e) {
    internalEvent = e;
}

// ---------------------- StateSearch ------------------------
StateSearch::StateSearch(StateMachine* sm) : stateMachine(sm) {}

void StateSearch::init() {
    internalState = InternalSearchState::ROTATE;
}

void StateSearch::enter(state_e from, state_event_e event) {
    if (from == STATE_WAIT) {
        //ASSERT2(false, "Invalid transition from WAIT without COMMAND");
        run();
    } else if (from == STATE_ATTACK || from == STATE_RETREAT) {
        if (event == STATE_EVENT_NONE) {
            //ASSERT2(from == STATE_ATTACK, "SEARCH_STATE_ENTER: NONE should only come from ATTACK");
            run();
        } else if (event == STATE_EVENT_FINISHED) {
            //assert(from == STATE_RETREAT && "SEARCH_STATE_ENTER: FINISHED should only come from RETREAT");
            if (internalState == InternalSearchState::FORWARD) {
                internalState = InternalSearchState::ROTATE;
            }
            run();
        } else {
            //assert(false && "SEARCH_STATE_ENTER: Unexpected event from ATTACK/RETREAT");
        }
    } else if (from == STATE_SEARCH) {
        if (event == STATE_EVENT_NONE) {
            return;
        } else if (event == STATE_EVENT_TIMEOUT) {
            if (internalState == InternalSearchState::ROTATE) {
                internalState = InternalSearchState::FORWARD;
            } else {
                internalState = InternalSearchState::ROTATE;
            }
            run();
        } else {
            //assert(false && "SEARCH_STATE_ENTER: Unexpected event from SEARCH");
        }
    } else if (from == STATE_MANUAL) {
        // Do nothing
    }
}

void StateSearch::run() {
    if (internalState == InternalSearchState::ROTATE) {
        drive_dir_e dir = (rand() % 2 == 0) ? DRIVE_DIR_ROTATE_LEFT : DRIVE_DIR_ROTATE_RIGHT;
        drive_set(dir, DRIVE_SPEED_MAX);
        timer_start(stateMachine->getTimer(), 800);
    } else if (internalState == InternalSearchState::FORWARD) {
        drive_set(DRIVE_DIR_FORWARD, DRIVE_SPEED_MAX);
        timer_start(stateMachine->getTimer(), 1200);
    }
}

// ---------------------- StateAttack ------------------------
StateAttack::StateAttack(StateMachine* sm) : stateMachine(sm) {}

void StateAttack::init() {
    internalState = InternalAttackState::FORWARD;
}

void StateAttack::enter(state_e from, state_event_e event) {
    InternalAttackState prevState = internalState;
    internalState = nextAttackState(stateMachine->getEnemy());

    if (from == STATE_SEARCH) {
        if (event == STATE_EVENT_ENEMY) {
            run();
        } else {
            //assert(false && "ATTACK: invalid event from SEARCH");
        }
    } else if (from == STATE_ATTACK) {
        if (event == STATE_EVENT_ENEMY) {
            if (prevState != internalState) {
                run();
            }
        } else if (event == STATE_EVENT_TIMEOUT) {
            //assert(false && "ATTACK: TIMEOUT received, consider alternative handling");
        } else {
            //assert(false && "ATTACK: invalid event from ATTACK");
        }
    } else if (from == STATE_RETREAT) {
        //assert(false && "ATTACK: should not enter from RETREAT");
    } else {
        //assert(false && "ATTACK: invalid from state");
    }
}

StateAttack::InternalAttackState StateAttack::nextAttackState(enemy_pos_e enemy) {
    switch (enemy) {
        case ENEMY_POS_FRONT: return InternalAttackState::FORWARD;
        case ENEMY_POS_LEFT: return InternalAttackState::LEFT;
        case ENEMY_POS_RIGHT: return InternalAttackState::RIGHT;
        default: 
        break;
        //assert(false && "Invalid enemy position"); return InternalAttackState::FORWARD;
    }
    return InternalAttackState::FORWARD;
}

void StateAttack::run() {
    switch (internalState) {
        case InternalAttackState::FORWARD:
            drive_set(DRIVE_DIR_FORWARD, DRIVE_SPEED_MAX);
            break;
        case InternalAttackState::LEFT:
            drive_set(DRIVE_DIR_ARCTURN_WIDE_LEFT, DRIVE_SPEED_MAX);
            break;
        case InternalAttackState::RIGHT:
            drive_set(DRIVE_DIR_ARCTURN_WIDE_RIGHT, DRIVE_SPEED_MAX);
            break;
    }
    timer_start(stateMachine->getTimer(), 4000);
}
// ---------------------- StateRetreat ------------------------

// Static retreat move table for StateRetreat
const StateRetreat::Move RETREAT_REVERSE[] = {
    { DRIVE_DIR_REVERSE, DRIVE_SPEED_MAX, 300 }
};

const StateRetreat::Move RETREAT_FORWARD[] = {
    { DRIVE_DIR_FORWARD, DRIVE_SPEED_MAX, 300 }
};

const StateRetreat::Move RETREAT_ROTATE_LEFT[] = {
    { DRIVE_DIR_ROTATE_LEFT, DRIVE_SPEED_FAST, 300 }
};

const StateRetreat::Move RETREAT_ROTATE_RIGHT[] = {
    { DRIVE_DIR_ROTATE_RIGHT, DRIVE_SPEED_MAX, 300 }
};

const StateRetreat::Move RETREAT_ARCTURN_LEFT[] = {
    { DRIVE_DIR_ARCTURN_SHARP_LEFT, DRIVE_SPEED_MAX, 300 }
};

const StateRetreat::Move RETREAT_ARCTURN_RIGHT[] = {
    { DRIVE_DIR_ARCTURN_SHARP_RIGHT, DRIVE_SPEED_MAX, 300 }
};

const StateRetreat::Move RETREAT_ALIGN_LEFT[] = {
    { DRIVE_DIR_REVERSE, DRIVE_SPEED_MAX, 250 },
    { DRIVE_DIR_ARCTURN_SHARP_LEFT, DRIVE_SPEED_MAX, 120 },
    { DRIVE_DIR_ARCTURN_MID_RIGHT, DRIVE_SPEED_MAX, 120 }
};

const StateRetreat::Move RETREAT_ALIGN_RIGHT[] = {
    { DRIVE_DIR_REVERSE, DRIVE_SPEED_MAX, 250 },
    { DRIVE_DIR_ARCTURN_SHARP_RIGHT, DRIVE_SPEED_MAX, 120 },
    { DRIVE_DIR_ARCTURN_MID_LEFT, DRIVE_SPEED_MAX, 120 }
};

// Define the static array in the cpp file
const StateRetreat::RetreatMove StateRetreat::retreatStates[] = {
    { RETREAT_REVERSE, 1 },
    { RETREAT_FORWARD, 1 },
    { RETREAT_ROTATE_LEFT, 1 },
    { RETREAT_ROTATE_RIGHT, 1 },
    { RETREAT_ARCTURN_LEFT, 1 },
    { RETREAT_ARCTURN_RIGHT, 1 },
    { RETREAT_ALIGN_LEFT, 3 },
    { RETREAT_ALIGN_RIGHT, 3 }
};

StateRetreat::StateRetreat(StateMachine* sm) : stateMachine(sm), moveIndex(0) {}

void StateRetreat::init() {
    internalState = InternalRetreatState::REVERSE;
    moveIndex = 0;
}

void StateRetreat::enter(state_e from, state_event_e event) {
    if (from == STATE_SEARCH || from == STATE_ATTACK) {
        if (event == STATE_EVENT_LINE) {
            run();
        } else {
            //assert(false && "RETREAT: Invalid event from SEARCH/ATTACK");
        }
    } else if (from == STATE_RETREAT) {
        if (event == STATE_EVENT_LINE) {
            run();
        } else if (event == STATE_EVENT_TIMEOUT) {
            moveIndex++;
            if (retreatStateDone()) {
                stateMachine->postInternalEvent(STATE_EVENT_FINISHED);
            } else {
                startRetreatMove();
            }
        } else if (event == STATE_EVENT_NONE || event == STATE_EVENT_ENEMY) {
            // Ignore
        } else {
            //assert(false && "RETREAT: Unexpected event from RETREAT");
        }
    } else {
        //assert(false && "RETREAT: Should not enter from this state");
    }
}


void StateRetreat::run() {
    moveIndex = 0;
    internalState = nextRetreatState();
    startRetreatMove();
}

void StateRetreat::startRetreatMove() {
    const RetreatMove& sequence = retreatStates[static_cast<int>(internalState)];
    //assert(moveIndex < sequence.moveCount);

    const Move& move = sequence.moves[moveIndex];
    drive_set(move.direction, move.speed);
    timer_start(stateMachine->getTimer(), move.duration);
}

bool StateRetreat::retreatStateDone() const {
    return moveIndex >= retreatStates[static_cast<int>(internalState)].moveCount;
}

StateRetreat::Move StateRetreat::currentMove() const {
    return retreatStates[static_cast<int>(internalState)].moves[moveIndex];
}

StateRetreat::InternalRetreatState StateRetreat::nextRetreatState() const {
    line_pos_e line = stateMachine->getLine();
    enemy_pos_e enemy = stateMachine->getEnemy();

    switch (line) {
        case LINE_FRONT_LEFT:
            if (enemy == ENEMY_POS_RIGHT || enemy == ENEMY_POS_FRONT) return InternalRetreatState::ALIGN_RIGHT;
            if (enemy == ENEMY_POS_LEFT) return InternalRetreatState::ALIGN_LEFT;
            return InternalRetreatState::REVERSE;

        case LINE_FRONT_RIGHT:
            if (enemy == ENEMY_POS_LEFT || enemy == ENEMY_POS_FRONT) return InternalRetreatState::ALIGN_LEFT;
            if (enemy == ENEMY_POS_RIGHT) return InternalRetreatState::ALIGN_RIGHT;
            return InternalRetreatState::REVERSE;

        case LINE_BACK_LEFT:
            if (currentMove().direction == DRIVE_DIR_REVERSE || internalState == InternalRetreatState::ARCTURN_RIGHT)
                return InternalRetreatState::ARCTURN_RIGHT;
            return InternalRetreatState::FORWARD;

        case LINE_BACK_RIGHT:
            if (currentMove().direction == DRIVE_DIR_REVERSE || internalState == InternalRetreatState::ARCTURN_LEFT)
                return InternalRetreatState::ARCTURN_LEFT;
            return InternalRetreatState::FORWARD;

        case LINE_FRONT:
            if (enemy == ENEMY_POS_FRONT) return InternalRetreatState::ARCTURN_LEFT;
            if (enemy == ENEMY_POS_RIGHT) return InternalRetreatState::ALIGN_RIGHT;
            return InternalRetreatState::REVERSE;

        case LINE_BACK:
            return InternalRetreatState::FORWARD;

        case LINE_LEFT:
            return InternalRetreatState::ARCTURN_RIGHT;

        case LINE_RIGHT:
            return InternalRetreatState::ARCTURN_LEFT;

        case LINE_DIAGONAL_LEFT:
        case LINE_DIAGONAL_RIGHT:
        case LINE_NONE:
            //assert(false && "RETREAT: Invalid or unexpected line position");
            return InternalRetreatState::REVERSE;
    }

    return InternalRetreatState::REVERSE;
}

// ----------------------- StateWait -------------------------
StateWait::StateWait(StateMachine* sm) : stateMachine(sm) {}

void StateWait::init() {}

void StateWait::enter(state_e from, state_event_e event) {
    //assert(from == STATE_WAIT && "WAIT: should only enter from WAIT");
}

void StateWait::run() {}

// ---------------------- StateManual ------------------------
StateManual::StateManual(StateMachine* sm) : stateMachine(sm) {}

void StateManual::init() {}

void StateManual::enter(state_e from, state_event_e event) {
    if (event != STATE_EVENT_COMMAND) return;

    ir_command_e cmd = stateMachine->getCommand();

    switch (cmd) {
        case CMD_TWO:
            drive_set(DRIVE_DIR_FORWARD, DRIVE_SPEED_MAX);
            break;
        case CMD_THREE:
            drive_set(DRIVE_DIR_REVERSE, DRIVE_SPEED_MAX);
            break;
        case CMD_FOUR:
            drive_set(DRIVE_DIR_ROTATE_LEFT, DRIVE_SPEED_MAX);
            break;
        case CMD_FIVE:
            drive_set(DRIVE_DIR_ROTATE_RIGHT, DRIVE_SPEED_MAX);
            break;
        case CMD_SIX:
            drive_stop();
            break;
        case CMD_ZERO:
            RESET;
            break;
        default:
            break;
    }
}

void StateManual::run() {}
