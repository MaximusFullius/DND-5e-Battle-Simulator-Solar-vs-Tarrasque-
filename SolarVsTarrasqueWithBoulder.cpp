#include <random>
#include <iostream>
#include <cmath>
using namespace std;

std::random_device rd; // obtain a random number from hardware.
std::mt19937 gen(rd()); // seed the generator.
std::uniform_int_distribution<> d20(1, 20);
std::uniform_int_distribution<> d8(1, 8);
std::uniform_int_distribution<> d10(1, 10);
std::uniform_int_distribution<> d6(1, 6);


int main(){
    // return value of 1 means the Solar won the fight.
    // return value of 2 means the Tarrasque won the fight.
    int numturns = 1;
    int tarrasqueHealth = 330;
    // Tarrasque hp = 676 (33d20 + 330) 
    for (int i = 1; i <= 33; i++){
        tarrasqueHealth += d20(gen); // roll d20
    }
    cout << "Tarrasque Health: " << tarrasqueHealth << "\n";

    int solarHealth = 114;
    // Tarrasque hp = 243 (18d10 + 144) 
    for (int i = 1; i < 18; i++){
        solarHealth += d10(gen); // roll d10
    }
    cout << "Solar Health: " << solarHealth << "\n";

    int solarAttackRoll = 0;
    int solarAttackDamage = 0;
    int tarrasqueAttackRoll = 0;
    int tarrasqueAttackDamage = 0;
    int solarAC = 21;
    int tarrasqueAC = 25;
    double tarrasqueMaxHP = 100.0;
    double dbTarrasqueHealthPercent = 100.0;
    int intTarrasqueHealthPercent = 100;
    bool crit = false;
    bool tCrit = false;
    bool tCritFail = false;
    bool critFail = false;
    int conSave = 1;
    int conSave1 = 1;
    int conSave2 = 1;
    int tarrasqueLegendaryResistancesRemaining = 3;
    double solarBonusAttackDamage = 0.0;
    int tarrasqueDexSave = 0;
    int solarHealCharges = 4;
    int solarHealAmount = 4;

    //cout << "Turn 1: Solar flies up into the air beyond the Tarrasque's reach and fires his Slaying Longbow. Let the cheese begin...\n";
    while (tarrasqueHealth > 0 && solarHealth > 0){
        //dbTarrasqueHealthPercent = tarrasqueHealth / tarrasqueMaxHP;
        //intTarrasqueHealthPercent = ceil(dbTarrasqueHealthPercent) * 100.0;
        
        if (solarHealth > 0){
            if (solarHealth <= 75 && solarHealCharges > 0){
                solarHealCharges--;
                solarHealAmount = 4;
                for (int i = 1; i <= 8; i++){
                    solarHealAmount += d8(gen);
                }
                solarHealth += solarHealAmount;
                cout << "Turn " << numturns << ": Solar heals for..." << solarHealAmount << " hp! Solar now has " << solarHealth << " hp remaining...\n";
            }
            else{
                cout << "Turn " << numturns << ": Solar attacks the Tarrasque with their Slaying Longbow and...";
                solarAttackDamage = 0;
                solarAttackRoll = d20(gen); //Solar rolls to hit.
                solarBonusAttackDamage = 0;
                if (solarAttackRoll == 20){ // Nat 20, critical hit
                    crit = true;
                }
                else{
                    crit = false;
                    //check for critical miss
                    if (solarAttackRoll == 1) { // Nat 1, critical miss
                        critFail = true;
                    }
                    else{
                        critFail = false;
                    }
                }
                solarAttackRoll += 13; // Solars' slaying longbow is +13 to hit.

                if (!critFail){
                    if (solarAttackRoll > tarrasqueAC){
                        solarAttackDamage = 6;
                        // Solars' Slaying Longbow Damage = (2d8 + 6) piercing damage plus 27 (6d8) radiant damage.
                        for (int i = 1; i <= 8; i++){
                            solarAttackDamage += d8(gen);
                        }
                        if (crit){ // Using bonus damage roll rule for critical hits.
                            solarAttackDamage += 6;
                            for (int i = 1; i <= 8; i++){
                                solarAttackDamage += d8(gen);
                            }
                            cout << "**CRITICALLY** "; // add to message for "*CRITICALLY* HITS for X damage!"
                        }
                        cout << "HITS for " << solarAttackDamage << " damage! ";
                        
                        tarrasqueHealth -= solarAttackDamage;
                    
                        //dbTarrasqueHealthPercent = tarrasqueHealth / tarrasqueMaxHP;
                        //intTarrasqueHealthPercent = ceil(dbTarrasqueHealthPercent) * 100;
                        if (tarrasqueHealth <= 0){
                            cout << "*THE SOLAR HAS KILLED THE TARRASQUE!!*\n";
                            return 1;
                        }
                        else{
                            cout << "The Tarrasque now has " << tarrasqueHealth << " hit points remaining. \n";

                            if (tarrasqueHealth <= 100){
                                cout << "*The Tarrasque has 100 hp or fewer remaining, so the Tarrasque must now roll a DC 15 con save against the instant death effect from the Solars' Slaying Longbow!*...\n";
                                cout << "The Tarrasque...";
                                // Tarrasques' Magic Resistance feature gives it advantage on saving throws against spells and other magical effects.
                                // "Advantage" means we roll twice and pick the larger number.
                                conSave1 = d20(gen) + 10; // Tarrasque has a consitution modifier of +10.
                                conSave2 = d20(gen) + 10;
                                if (conSave1 >= conSave2) conSave = conSave1;
                                else conSave = conSave2;
                                if (conSave < 15){ 
                                    if (conSave == 10){ // nat 1 always fails.
                                        cout << "CRITICALLY ";
                                    }
                                    cout << "FAILS the con save against the Solars' Slaying Longbow! Does the Tarrasque have any Legendary Resistance usages remaining?...\n";
                                    if (tarrasqueLegendaryResistancesRemaining > 0){
                                        cout << "*IT DOES!* The Tarrasque has " << tarrasqueLegendaryResistancesRemaining << " charges of its' Legendary Resistance remaining and so uses one to stay alive here!\n";
                                        tarrasqueLegendaryResistancesRemaining--;
                                    }
                                    else{
                                        cout << "*IT DOES NOT!* The Tarrasque doesn't have any more Legendary Resistance Charges remaining and *DIES INSTANTLY* to the Solar!\n";
                                        tarrasqueHealth = 0;
                                        return 1;
                                    }
                                }
                                else{
                                    cout << "SUCCEEDS the con save against the Solars' Slaying Longbow and LIVES ON!\n";
                                }
                            }
                            
                        }
                    }
                    else{ // solar attack misses
                        cout << "MISSES the Tarrasque! The Tarrasque still has " << tarrasqueHealth << " hit points remaining.\n";
                    }
                }
                else{ // crit fail
                    cout << "CRITICALLY MISSES the Tarrasque! The Tarrasque still has " << tarrasqueHealth << " hit points remaining.\n";
                }
            } 
        }

        // ----------------------------- TARRASQUE TURN ---------------------------

        if (tarrasqueHealth > 0){
            cout << "Turn " << numturns << ": Tarrasque attacks the Solar with their Boulder and...";
            tarrasqueAttackDamage = 0;
            tarrasqueAttackRoll = d20(gen); //Tarrasque rolls to hit.
            if (tarrasqueAttackRoll == 20){ // Nat 20, critical hit
                tCrit = true;
            }
            else{
                tCrit = false;
                //check for critical miss
                if (tarrasqueAttackRoll == 1) { // Nat 1, critical miss
                    tCritFail = true;
                }
                else{
                    tCritFail = false;
                }
            }
            tarrasqueAttackRoll += 10; // Tarrasques' Boulder is +10 to hit.

            if (!tCritFail){
                if (tarrasqueAttackRoll > solarAC){
                    tarrasqueAttackDamage = 10;
                    // Tarrasque' Boulder Damage =  4d10+10 bludgeoning. Since this is not magical damage, the solar actually takes only half of it.
                    for (int i = 1; i <= 4; i++){
                        tarrasqueAttackDamage += d10(gen);
                    }
                    if (tCrit){ // Using bonus damage roll rule for critical hits.
                        tarrasqueAttackDamage += 10;
                        for (int i = 1; i <= 4; i++){
                            tarrasqueAttackDamage += d10(gen);
                        }
                        cout << "**CRITICALLY** "; // add to message for "*CRITICALLY* HITS for X damage!"
                    }
                    tarrasqueAttackDamage = ceil(tarrasqueAttackDamage / 2); // Since this attack is not magical damage, the solar actually takes only half of the damage due to its resistances.
                    solarHealth -= tarrasqueAttackDamage;
                    //dbTarrasqueHealthPercent = tarrasqueHealth / tarrasqueMaxHP;
                    //intTarrasqueHealthPercent = ceil(dbTarrasqueHealthPercent) * 100;
                    cout << "HITS for " << tarrasqueAttackDamage << " damage! \n";
                    if (solarHealth <= 0){
                        cout << "*THE TARRASQUE HAS KILLED THE SOLAR!!*\n";
                        return 2;
                    }
                    else{
                        cout << "The Solar now has " << solarHealth << " hit points remaining. \n";
                    }
                }
                else{ // solar attack misses
                cout << "MISSES the Solar! The Solar still has " << solarHealth << " hit points remaining.\n";
                }
            }
            else{ // crit fail
                cout << "CRITICALLY MISSES the Solar! The Solar still has " << solarHealth << " hit points remaining.\n";
            }

            // **SECOND BOULDER**
            /*
            if (solarHealth > 0){
                cout << "Turn " << numturns << ": Tarrasque attacks the Solar with a second Boulder and...";
                tarrasqueAttackDamage = 0;
                tarrasqueAttackRoll = d20(gen); //Tarrasque rolls to hit.
                if (tarrasqueAttackRoll == 20){ // Nat 20, critical hit
                    tCrit = true;
                }
                else{
                    tCrit = false;
                    //check for critical miss
                    if (tarrasqueAttackRoll == 1) { // Nat 1, critical miss
                        tCritFail = true;
                    }
                    else{
                        tCritFail = false;
                    }
                }
                tarrasqueAttackRoll += 10; // Tarrasques' Boulder is  is +10 to hit.

                if (!tCritFail){
                    if (tarrasqueAttackRoll > solarAC){
                        tarrasqueAttackDamage = 10;
                        // Tarrasque' Boulder Damage =  4d10+10 bludgeoning. Since this is not magical damage, the solar actually takes only half of it.
                        for (int i = 1; i <= 4; i++){
                            tarrasqueAttackDamage += d10(gen);
                        }
                        if (tCrit){ // Using bonus damage roll rule for critical hits.
                            tarrasqueAttackDamage += 10;
                            for (int i = 1; i <= 4; i++){
                                tarrasqueAttackDamage += d10(gen);
                            }
                            cout << "**CRITICALLY** "; // add to message for "*CRITICALLY* HITS for X damage!"
                        }
                        tarrasqueAttackDamage = ceil(tarrasqueAttackDamage / 2); // Since this attack is not magical damage, the solar actually takes only half of the damage due to its resistances.
                        solarHealth -= tarrasqueAttackDamage;
                        //dbTarrasqueHealthPercent = tarrasqueHealth / tarrasqueMaxHP;
                        //intTarrasqueHealthPercent = ceil(dbTarrasqueHealthPercent) * 100;
                        cout << "HITS for " << tarrasqueAttackDamage << " damage! \n";
                        if (solarHealth <= 0){
                            cout << "*THE TARRASQUE HAS KILLED THE SOLAR!!*\n";
                            return 2;
                        }
                        else{
                            cout << "The Solar now has " << solarHealth << " hit points remaining. \n";
                        }
                    }
                    else{ // solar attack misses
                    cout << "MISSES the Solar! The Solar still has " << solarHealth << " hit points remaining.\n";
                    }
                }
                else{ // crit fail
                    cout << "CRITICALLY MISSES the Solar! The Solar still has " << solarHealth << " hit points remaining.\n";
                }
            }
            */
        }
        
        //-----------------------------------------------------------

        cout << "\n";
        numturns++;
    }
    if (solarHealth > 0  && tarrasqueHealth <= 0){
        cout << "It took " << numturns << " rounds for the Solar to kill the Tarrasque!\n";
        return 1;
    }
    else {
        cout << "It took " << numturns << " rounds for the Tarrasque to kill the Solar!\n";
        return 2;
    }
}
