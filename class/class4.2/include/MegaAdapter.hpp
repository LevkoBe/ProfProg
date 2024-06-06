#pragma once

#include <iostream>
#include <LegacyCalculator.hpp>
#include <ModernCalculators.hpp>

class MegaAdapter : public BaseMegaCalculator {
    std::unique_ptr<LegacyCalculator> legacyCalc;
public:
    MegaAdapter(std::unique_ptr<LegacyCalculator> legacyCalc): legacyCalc(std::move(legacyCalc)) {}
    double getPrice() const override {
        double partOne = legacyCalc->calculatePricePart1();
        double partTwo = legacyCalc->calculatePricePart2();
        return partOne + partTwo;
    }
    
    double getMinimalValue() const override {
        return legacyCalc->getOurTheMostAndMinimalValue();
    }

    std::string getReport() const override {
        return legacyCalc->getSomeDocumentRepresentation();
    }
};