#include "StandardPriceDecorator.h"

StandardPriceDecorator::StandardPriceDecorator(IStrategy *strategy_, Vector3 pos_, Vector3 des_, IEntity* entity_) 
  : PriceDecorator(strategy_, pos_, des_) {
      entity = entity_;
      std::cout << "Estimated price " << GetEstimatedPrice() << std::endl;
  }

void StandardPriceDecorator::Move(IEntity* drone, double dt) {
    double cost = price_per_sec * dt;
    Wallet* wallet = entity->GetWallet();
    std::cout << "Cost of move is " << cost << std::endl;
    std::cout << "Current wallet balance: " << wallet->getBalance() << std::endl;
    if (wallet->getBalance() < cost) {
        std::cout << "No more funds left in wallet, ending trip" << std::endl;
        insufficientFunds = true;
    } else {
        std::cout << "Withdrawing " << cost << " from wallet" << std::endl;
        wallet->withdraw(cost);
        strategy->Move(drone, dt);
    }
}

bool StandardPriceDecorator::IsCompleted() {
    bool completed = strategy->IsCompleted() || insufficientFunds;
    std::cout << "Completed " << completed << std::endl;
    return completed;
}

float StandardPriceDecorator::GetEstimatedPrice() {
    return estimatedDistance * .015; // .0015
}
