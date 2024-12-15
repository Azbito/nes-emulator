#ifndef ASSEMBLY_H
#define ASSEMBLY_H

#include "CPU6502.hpp"
#include <map>
#include <functional>
#include <iostream>
#include <stdint.h>

using namespace std;

class CPU6502;

class Assembly
{
public:
    Assembly(CPU6502 *cpu) : cpu(cpu) {};

    static map<uint8_t, function<void(Assembly &)>> opcodeMap;
    void executeOpcode(uint8_t opcode);
    void brkHandler();
    void oraIzxHandler();
    void sloIzxHandler();
    void nopZpHandler();
    void oraZpHandler();
    void aslZpHandler();
    void sloZpHandler();
    void phpHandler();
    void oraImmHandler();
    void aslAHandler();
    void ancImmHandler();
    void nopAbsHandler();
    void oraAbsHandler();
    void aslAbsHandler();
    void sloAbsHandler();
    void bplHandler();
    void oraIzyHandler();
    void sloIzyHandler();
    void jsrAbsHandler();
    void andIzxHandler();
    void rlaIzxHandler();
    void bitZpHandler();
    void andZpHandler();
    void rolZpHandler();
    void rlaZpHandler();
    void plpHandler();
    void andImmHandler();
    void rolAHandler();
    void bitAbsHandler();
    void andAbsHandler();
    void rolAbsHandler();
    void rlaAbsHandler();
    void bmiRelHandler();
    void andIzyHandler();
    void rlaIzyHandler();
    void nopZpxHandler();
    void andZpxHandler();
    void rolZpxHandler();
    void rlaZpxHandler();
    void secHandler();
    void andAbyHandler();
    void nopHandler();
    void rlaAbyHandler();
    void nopAbxHandler();
    void andAbxHandler();
    void rolAbxHandler();
    void rlaAbxHandler();
    void rtiHandler();
    void eorIzxHandler();
    void sreIzxHandler();
    void eorZpHandler();
    void lsrZpHandler();
    void sreZpHandler();
    void phaHandler();
    void eorImmHandler();
    void lsrHandler();
    void alrHandler();
    void jmpAbsHandler();
    void eorAbsHandler();
    void lsrAbsHandler();
    void sreAbsHandler();
    void bvcRelHandler();
    void eorIzyHandler();
    void sreIzyHandler();
    void adcIzxHandler();
    void rraIzxHandler();
    void adcZpHandler();
    void rorZpHandler();
    void rraZpHandler();
    void eorZpxHandler();
    void lsrZpxHandler();
    void sreZpxHandler();
    void cliHandler();
    void eorAbyHandler();
    void eorAbxHandler();
    void lsrAbxHandler();
    void sreAbxHandler();
    void rtsHandler();
    void bvsHandler();
    void adcIzyHandler();
    void rraIzyHandler();
    void adcZpxHandler();
    void rorZpxHandler();
    void rraZpxHandler();
    void seiHandler();
    void adcAbyHandler();
    void adcAbxHandler();
    void rorAbxHandler();
    void rraAbxHandler();
    void staAbxHandler();
    void nopImmHandler();
    void staIzxHandler();
    void saxIzxHandler();
    void styZpHandler();
    void staZpHandler();
    void stxZpHandler();
    void saxZpHandler();
    void ldyImmHandler();
    void ldaIzxHandler();
    void ldxImmHandler();
    void laxIzxHandler();
    void ldyZpHandler();
    void ldaZpHandler();
    void ldxZpHandler();
    void laxZpHandler();
    void tayHandler();
    void ldaImmHandler();
    void taxHandler();
    void laxImmHandler();
    void ldyAbsHandler();
    void ldaAbsHandler();
    void ldxAbsHandler();
    void laxAbsHandler();
    void bcsRelHandler();
    void ldaIzyHandler();
    void laxIzyHandler();
    void ldyZpxHandler();
    void ldaZpxHandler();
    void ldxZpyHandler();
    void laxZpyHandler();
    void clvHandler();
    void ldaAbyHandler();
    void tsxHandler();
    void lasAbyHandler();
    void ldxAbxHandler();
    void ldaAbxHandler();
    void ldxAbyHandler();
    void laxAbyHandler();
    void cmpAbsHandler();
    void cmpZpHandler();
    void cldHandler();
    void cmpIzyHandler();
    void dcpIzyHandler();
    void kilHandler();
    void ancImHandler();
    void arrImHandler();
    void ahxAbsHandler();
    void oraZpxHandler();
    void aslZpxHandler();
    void sloZpxHandler();
    void oraAbyHandler();
    void sloAbyHandler();
    void oraAbxHandler();
    void aslAbxHandler();
    void sloAbxHandler();
    void sreAbyHandler();
    void plaHandler();
    void adcImmHandler();
    void rorHandler();
    void arrHandler();
    void jmpIndHandler();
    void adcAbsHandler();
    void rorAbsHandler();
    void rraAbsHandler();
    void crashHandler();
    void rraAbyHandler();
    void deyHandler();
    void txaHandler();
    void xaaImmHandler();
    void styAbsHandler();
    void staAbsHandler();
    void stxAbsHandler();
    void saxAbsHandler();
    void bccHandler();
    void staIzyHandler();
    void ahxIzyHandler();
    void styZpxHandler();
    void staZpxHandler();
    void stxZpyHandler();
    void saxZpyHandler();
    void tyaHandler();
    void staAbyHandler();
    void txsHandler();
    void tasAbyHandler();
    void shyAbxHandler();
    void shxAbyHandler();
    void ahxAbyHandler();
    void bcsHandler();
    void ldyAbxHandler();
    void cpyImmHandler();
    void cmpIzxHandler();
    void dcpIzxHandler();
    void cpyZpHandler();
    void decZpHandler();
    void dcpZpHandler();
    void inyHandler();
    void cmpImmHandler();
    void dexHandler();
    void axsImmHandler();
    void cpyAbsHandler();
    void decAbsHandler();
    void dcpAbsHandler();
    void bneHandler();
    void cmpZpxHandler();
    void decZpxHandler();
    void dcpZpxHandler();
    void cmpAbyHandler();
    void dcpAbyHandler();
    void cmpAbxHandler();
    void decAbxHandler();
    void dcpAbxHandler();
    void sbcIzxHandler();
    void iscIzxHandler();
    void sbcZpHandler();
    void incZpHandler();
    void iscZpHandler();
    void inxHandler();
    void sbcImmHandler();
    void cpxAbsHandler();
    void sbcAbsHandler();
    void incAbsHandler();
    void iscAbsHandler();
    void beqHandler();
    void sbcIzyHandler();
    void iscIzyHandler();
    void sbcZpxHandler();
    void incZpxHandler();
    void iscZpxHandler();
    void sedHandler();
    void sbcAbyHandler();
    void cpxImmHandler();
    void cpxZpHandler();
    void iscAbyHandler();
    void sbcAbxHandler();
    void incAbxHandler();
    void iscAbxHandler();

private:
    CPU6502 *cpu;
};

#endif // ASSEMBLY_H