#include <random>
#include <iostream>
#include <cmath>
using namespace std;

int rando = 0;
std::random_device rd; // obtain a random number from hardware.
std::mt19937 gen(rd()); // seed the generator.
std::uniform_int_distribution<> d20(1, 20);
std::uniform_int_distribution<> d8(1, 8);
std::uniform_int_distribution<> d10(1, 10);


int main(){
    int numturns = 2;
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
    int tarrasqueAC = 25;
    double tarrasqueMaxHP = 100.0;
    double dbTarrasqueHealthPercent = 100.0;
    int intTarrasqueHealthPercent = 100;
    bool crit = false;
    bool critFail = false;
    int conSave = 1;
    int conSave1 = 1;
    int conSave2 = 1;
    int tarrasqueLegendaryResistancesRemaining = 3;

    cout << "Turn 1: Solar flies up into the air beyond the Tarrasque's reach and fires his Slaying Longbow. Let the cheese begin...\n";
    while (tarrasqueHealth > 0){
        dbTarrasqueHealthPercent = tarrasqueHealth / tarrasqueMaxHP;
        intTarrasqueHealthPercent = ceil(dbTarrasqueHealthPercent) * 100;
        cout << "Turn " << numturns << ": Solar attacks the Tarrasque with their Slaying Longbow and...";
        solarAttackDamage = 0;
        solarAttackRoll = d20(gen); //Solar rolls to hit.
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
                tarrasqueHealth -= solarAttackDamage;
                dbTarrasqueHealthPercent = tarrasqueHealth / tarrasqueMaxHP;
                intTarrasqueHealthPercent = ceil(dbTarrasqueHealthPercent) * 100;
                cout << "HITS for " << solarAttackDamage << " damage! ";
                if (tarrasqueHealth <= 0){
                    cout << "*THE SOLAR HAS KILLED THE TARRASQUE!!*\n";
                    break;
                }
                else{
                    cout << "The Tarrasque now has " << tarrasqueHealth << " hit points, or " << intTarrasqueHealthPercent << " percent of its' health remaining. \n";
                }

                if (tarrasqueHealth <= 100 && tarrasqueHealth > 0){
                    
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
                            break;
                        }
                    }
                    else{
                        cout << "SUCCEEDS the con save against the Solars' Slaying Longbow and LIVES ON!\n";
                    }
                }
            }
            else{ // solar attack misses

              cout << "MISSES the Tarrasque! The Tarrasque still has " << tarrasqueHealth << " hit points, or " << intTarrasqueHealthPercent << " percent of its' health remaining.\n";
            }
        }
        else{ // crit fail
            cout << "CRITICALLY MISSES the Tarrasque! The Tarrasque still has " << tarrasqueHealth << " hit points, or " << intTarrasqueHealthPercent << "percent of its' health remaining.\n";
        }
        numturns++;
    }
    cout << "It took " << numturns << " turns for the Solar to kill the Tarrasque!";
}
