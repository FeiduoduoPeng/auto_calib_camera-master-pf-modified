#include "myWriteMySQL.h"

/***
 * @ctype type of camera, choose from "bino_cam", "mono_cam" and "rgbd"
 * */
bool myWriteMySQL(const std::string &cuuid, const std::string &cmatrix, const std::string &ctype){
    using namespace std;
    string s( "insert into camera_params \
                    (camera_uuid, camera_param, camera_type) \
                    values \
                    (?, ?, ?)");
    try {
        sql::Driver *driver;
        sql::Connection *con;
        sql::Statement *stmt;
        sql::ResultSet *res;
        sql::PreparedStatement *pstmt;

        /* Create a connection */
        driver = get_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", "root", "leisure");
        /* Connect to the MySQL test database */
        con->setSchema("camera_xxtrinsics");

        pstmt = con->prepareStatement(s.c_str());
        pstmt->setString(1,cuuid);
        pstmt->setString(2,cmatrix);
        pstmt->setString(3,ctype);
        pstmt->executeUpdate();

        //stmt = con->createStatement();
        //res = stmt->executeQuery(s.c_str());
        delete res;
        delete stmt;
        delete con;
    } catch (sql::SQLException &e) {
        //cout << "# ERR: SQLException in " << __FILE__;
        //cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        //cout << "# ERR: " << e.what();
        //cout << " (MySQL error code: " << e.getErrorCode();
        //cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
    return true;
}