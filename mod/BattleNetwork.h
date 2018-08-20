#pragma once

#include "asio.hpp"
#include "BattleMenu.h"
#include <thread>
#include <memory>


// #define _WIN32_WINNT 0x0A00

class BattleNetwork {
public:
    // , strand_(io_context_) 
    BattleNetwork() : socket_(io_context_), work_(io_context_){};

    virtual ~BattleNetwork() {
        io_context_.stop();
        if (worker_.joinable()) worker_.join();
    }

    void asyncRun() {
        /*
        printf("asyncRun started\n");
        if (worker_.joinable())
            worker_.join();
        */
        worker_ = std::thread([this] {
            printf("spawning thread\n");
            io_context_.run();
            printf("threading is done\n");
        });
    }

    virtual bool getRandSeed(unsigned int& seed) = 0;

    // ������սid������roles���
    virtual void rDataHandshake(std::vector<RoleSave>& my_roles, std::vector<RoleSave>& roles) = 0;

    struct SerializableBattleAction
    {
        int Action;
        int MoveX, MoveY;
        int ActionX, ActionY;
        int magicID = 0;
        int itemID = -1;
        void print() {
            printf("action %d, movex %d, movey %d, actionx %d, actiony %d magic %d, item %d\n", Action, MoveX, MoveY, ActionX, ActionY, magicID, itemID);
        }
    };
    static_assert(sizeof(SerializableBattleAction) == 28, "introduced extra struct padding");

    // ÿ���ж����� ����Action��ȥ ���ҽ���
    bool sendMyAction(const BattleNetwork::SerializableBattleAction& action);

    // async���ɹ���
    bool getOpponentAction(BattleNetwork::SerializableBattleAction& action, std::function<void(std::error_code err, std::size_t bytes)> f);

    bool isHost();

protected:
    asio::io_context io_context_;
    asio::ip::tcp::socket socket_;
    asio::io_service::work  work_;
    // asio::io_context::strand strand_;
    bool is_host_;
    std::thread worker_;

};


class BattleHost : public BattleNetwork {
public:
    BattleHost();
    bool getRandSeed(unsigned int& seed) override;
    void rDataHandshake(std::vector<RoleSave>& my_roles, std::vector<RoleSave>& roles) override;
};

class BattleClient : public BattleNetwork {
public:
    BattleClient(const std::string& host, const std::string& port);
    bool getRandSeed(unsigned int& seed) override;
    void rDataHandshake(std::vector<RoleSave>& my_roles, std::vector<RoleSave>& roles) override;
};

class BattleNetworkFactory {
public:
    // �ȴ�����
    static std::unique_ptr<BattleNetwork> MakeHost();
    static std::unique_ptr<BattleNetwork> MakeClient(const std::string& host, const std::string& port);
};
