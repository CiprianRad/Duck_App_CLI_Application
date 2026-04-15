#include <cassert>
#include <iostream>
#include <memory>
#include <vector>
#include <fstream>
#include <cstdio>
#include <sstream>
#include "../src/ro/ubb/duck_app/domain/Duck.h"
#include "../src/ro/ubb/duck_app/domain/Lane.h"
#include "../src/ro/ubb/duck_app/domain/Validators.h"
#include "../src/ro/ubb/duck_app/repository/Repository.h"
#include "../src/ro/ubb/duck_app/repository/FileRepository.h"
#include "../src/ro/ubb/duck_app/service/DuckService.h"
#include "../src/ro/ubb/duck_app/service/LaneService.h"
#include "../src/ro/ubb/duck_app/service/ReportsService.h"
#include "../src/ro/ubb/duck_app/ui/Console.h"

using namespace ro::ubb::duck_app::domain;
using namespace ro::ubb::duck_app::repository;
using namespace ro::ubb::duck_app::service;
using namespace ro::ubb::duck_app::ui;
/*
    private:
        void uiAddDuck();
        void uiUpdateDuck();
        void uiDeleteDuck();
        void uiShowAllDucks();
        void uiAddLane();
        void uiUpdateLane();
        void uiDeleteLane();
        void uiShowAllLanes();
        void uiShowOptimalTime();
        static void showAllOptions();
        static void showDuckOptions();
        static void showLaneOptions();
        static void showReportsOptions();
*/
// They are private. I should probably make them public or at least protected for testing,
// or just test them through runMenu by providing a complex string to cin.

void testDomain() {
    Duck d(1, 10, 20);
    assert(d.getId() == 1);
    assert(d.getSpeed() == 10);
    assert(d.getResistance() == 20);

    d.setDuck_id(2);
    d.setSpeed(15);
    d.setResistance(25);
    assert(d.getId() == 2);
    assert(d.getSpeed() == 15);
    assert(d.getResistance() == 25);

    Duck d2;
    assert(d2.getId() == 0);

    std::stringstream ss;
    ss << d;
    assert(ss.str().find("Duck ID: 2") != std::string::npos);

    std::stringstream ss_in("3 30 40");
    ss_in >> d2; 
    assert(d2.getId() == 3);
    assert(d2.getSpeed() == 30);
    assert(d2.getResistance() == 40);

    Lane l(1, 100);
    assert(l.getId() == 1);
    assert(l.getLength() == 100);

    l.setLane_id(2);
    l.setLength(200);
    assert(l.getId() == 2);
    assert(l.getLength() == 200);

    Lane l2;
    assert(l2.getId() == 0);

    std::stringstream ss_l;
    ss_l << l;
    assert(ss_l.str().find("Lane ID: 2") != std::string::npos);

    std::stringstream ss_l_in("3 300");
    ss_l_in >> l2;
    assert(l2.getId() == 3);
    assert(l2.getLength() == 300);

    DuckValidator dv;
    Duck d1_valid(1, 10, 20);
    dv.validate(d1_valid);

    try {
        Duck d2_invalid(-1, 10, 20);
        dv.validate(d2_invalid);
        assert(false);
    } catch (const ValidatorException& e) {
        assert(std::string(e.what()).find("Id") != std::string::npos);
    }

    try {
        Duck d3_invalid(1, 0, 20);
        dv.validate(d3_invalid);
        assert(false);
    } catch (const ValidatorException& e) {
        assert(std::string(e.what()).find("Speed") != std::string::npos);
    }

    try {
        Duck d4_invalid(1, 10, 0);
        dv.validate(d4_invalid);
        assert(false);
    } catch (const ValidatorException& e) {
        assert(std::string(e.what()).find("Resistance") != std::string::npos);
    }

    try {
        Lane temp_lane(1, 100);
        dv.validate(temp_lane);
        assert(false);
    } catch (const ValidatorException& e) {
        assert(std::string(e.what()).find("Duck must be a duck") != std::string::npos);
    }

    LaneValidator lv;
    Lane l1_valid(1, 100);
    lv.validate(l1_valid);

    try {
        Lane l2_invalid(-1, 100);
        lv.validate(l2_invalid);
        assert(false);
    } catch (const ValidatorException& e) {
        assert(std::string(e.what()).find("Id") != std::string::npos);
    }

    try {
        Lane l3_invalid(1, 0);
        lv.validate(l3_invalid);
        assert(false);
    } catch (const ValidatorException& e) {
        assert(std::string(e.what()).find("Length") != std::string::npos);
    }

    try {
        Duck temp_duck(1, 10, 20);
        lv.validate(temp_duck);
        assert(false);
    } catch (const ValidatorException& e) {
        assert(std::string(e.what()).find("Lane must be a lane") != std::string::npos);
    }

    BaseEntityValidator bev;
    bev.validate(d1_valid);
    try {
        Duck d_invalid_id(-1, 10, 20);
        bev.validate(d_invalid_id);
        assert(false);
    } catch (const ValidatorException&) {}

    std::cout << "Domain tests passed!" << std::endl;
}

void testRepository() {
    auto validator = std::make_shared<DuckValidator>();
    Repository repo(validator);

    auto d1 = std::make_shared<Duck>(1, 10, 20);
    repo.save(d1);
    assert(repo.findAll().size() == 1);
    assert(repo.findById(1)->getId() == 1);

    auto d2 = std::make_shared<Duck>(2, 15, 25);
    repo.save(d2);
    assert(repo.findAll().size() == 2);

    try {
        repo.save(d1);
        assert(false);
    } catch (const RepositoryException&) {}

    auto d3 = std::make_shared<Duck>(1, 12, 22);
    repo.update(d3);
    auto found = std::static_pointer_cast<Duck>(repo.findById(1));
    assert(found->getSpeed() == 12);

    auto d4 = std::make_shared<Duck>(4, 10, 20);
    try {
        repo.update(d4);
        assert(false);
    } catch (const RepositoryException&) {}

    repo.deleteById(1);
    assert(repo.findAll().size() == 1);
    assert(repo.findById(1) == nullptr);

    try {
        repo.deleteById(1);
        assert(false);
    } catch (const RepositoryException&) {}

    std::cout << "Repository tests passed!" << std::endl;
}

void testFileRepository() {
    const std::string filename = "test_ducks.txt";
    {
        std::ofstream out(filename);
        out << "1 0\n10\n20\n\n"; // 1 duck, 0 lanes
        out.close();
    }

    auto validator = std::make_shared<DuckValidator>();
    FileRepository repo(validator, filename);
    assert(repo.findAll().size() == 1);
    
    auto d1 = std::make_shared<Duck>(2, 15, 25);
    repo.save(d1);
    assert(repo.findAll().size() == 2);

    auto d2 = std::make_shared<Duck>(1, 12, 22);
    repo.update(d2);
    
    repo.deleteById(1);
    assert(repo.findAll().size() == 1);

    const std::string filename_l = "test_lanes.txt";
    {
        std::ofstream out(filename_l);
        out << "0 1\n\n\n100\n";
        out.close();
    }
    auto l_validator = std::make_shared<LaneValidator>();
    FileRepository repo_l(l_validator, filename_l);
    assert(repo_l.findAll().size() == 1);

    std::remove(filename.c_str());
    std::remove(filename_l.c_str());
    std::cout << "FileRepository tests passed!" << std::endl;
}

void testServices() {
    auto d_repo = std::make_shared<Repository>(std::make_shared<DuckValidator>());
    DuckService d_service(d_repo);

    d_service.addDuck(1, 10, 20);
    assert(d_service.getDucks().size() == 1);
    assert(d_service.findDuckById(1)->getId() == 1);
    assert(d_service.getDuckRepository() == d_repo);

    d_service.updateDuck(1, 15, 25);
    assert(d_service.findDuckById(1)->getSpeed() == 15);

    d_service.removeDuck(1);
    assert(d_service.getDucks().empty());

    auto l_repo = std::make_shared<Repository>(std::make_shared<LaneValidator>());
    LaneService l_service(l_repo);

    l_service.addLane(1, 100);
    assert(l_service.getLanes().size() == 1);
    assert(l_service.findLaneById(1)->getId() == 1);
    assert(l_service.getRepository() == l_repo);

    l_service.updateLane(1, 200);
    assert(l_service.findLaneById(1)->getLength() == 200);

    l_service.removeLane(1);
    assert(l_service.getLanes().empty());

    std::cout << "Service tests passed!" << std::endl;
}

void testReportsService() {
    auto d_repo = std::make_shared<Repository>(std::make_shared<DuckValidator>());
    auto l_repo = std::make_shared<Repository>(std::make_shared<LaneValidator>());
    ReportsService r_service(d_repo, l_repo);

    r_service.schemaMunti();

    d_repo->save(std::make_shared<Duck>(1, 10, 20));
    l_repo->save(std::make_shared<Lane>(1, 100));

    assert(r_service.getDuckRepository() == d_repo);
    assert(r_service.getLaneRepository() == l_repo);

    r_service.schemaMunti();

    d_repo->save(std::make_shared<Duck>(2, 20, 10));
    l_repo->save(std::make_shared<Lane>(2, 200));

    r_service.schemaMunti();

    d_repo->save(std::make_shared<Duck>(3, 5, 30));
    r_service.schemaMunti();

    auto d_repo2 = std::make_shared<Repository>(std::make_shared<DuckValidator>());
    auto l_repo2 = std::make_shared<Repository>(std::make_shared<LaneValidator>());
    r_service.setDuckRepository(d_repo2);
    r_service.setLaneRepository(l_repo2);
    assert(r_service.getDuckRepository() == d_repo2);
    assert(r_service.getLaneRepository() == l_repo2);

    std::cout << "ReportsService tests passed!" << std::endl;
}

void testUI() {
    auto d_service = std::make_shared<DuckService>(std::make_shared<Repository>(std::make_shared<DuckValidator>()));
    auto l_service = std::make_shared<LaneService>(std::make_shared<Repository>(std::make_shared<LaneValidator>()));
    auto r_service = std::make_shared<ReportsService>(d_service->getDuckRepository(), l_service->getRepository());
    UI ui(d_service, l_service, r_service);

    assert(ui.getDuckService() == d_service);
    assert(ui.getLaneService() == l_service);
    assert(ui.getReportsService() == r_service);

    // Test runMenu with a lot of inputs to cover many lines
    std::stringstream ss;
    // 1. Duck options -> 4. Show all ducks -> x. Back
    ss << "1\n4\nx\n";
    // 1. Duck options -> 1. Add a duck (1, 10, 20) -> x. Back
    ss << "1\n1\n1\n10\n20\nx\n";
    // 1. Duck options -> 2. Update a duck (1, 15, 25) -> x. Back
    ss << "1\n2\n1\n15\n25\nx\n";
    // 1. Duck options -> 3. Delete a duck (1) -> x. Back
    ss << "1\n3\n1\nx\n";
    
    // 2. Lane options -> 4. Show all lanes -> x. Back
    ss << "2\n4\nx\n";
    // 2. Lane options -> 1. Add a lane (1, 100) -> x. Back
    ss << "2\n1\n1\n100\nx\n";
    // 2. Lane options -> 2. Update a lane (1, 200) -> x. Back
    ss << "2\n2\n1\n200\nx\n";
    // 2. Lane options -> 3. Delete a lane (1) -> x. Back
    ss << "2\n3\n1\nx\n";

    // 3. Reports options -> 1. Show optimal time -> x. Back
    ss << "3\n1\nx\n";
    
    // x. Exit
    ss << "x\n";

    std::streambuf* orig_cin = std::cin.rdbuf(ss.rdbuf());
    std::stringstream ss_err;
    std::streambuf* orig_cerr = std::cerr.rdbuf(ss_err.rdbuf());
    
    ui.runMenu();
    
    std::cin.rdbuf(orig_cin);
    std::cerr.rdbuf(orig_cerr);

    std::cout << "UI tests passed!" << std::endl;
}

int main() {
    testDomain();
    testRepository();
    testFileRepository();
    testServices();
    testReportsService();
    testUI();
    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}
