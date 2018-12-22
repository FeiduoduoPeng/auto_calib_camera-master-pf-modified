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
    string ss( "insert into camera_params \
                    (camera_uuid, camera_param, camera_type) \
                    values \
                    (?, ?, ?) \
                    on duplicate key update \
                    camera_param=?, camera_type=? ");
    try {
        sql::Driver *driver;
        sql::Connection *con;// = new sql::Connection;
//        sql::Statement *stmt;// = new sql::Statement;
//        sql::ResultSet *res;// = new sql::ResultSet;
        sql::PreparedStatement *pstmt;

        /* Create a connection */
        driver = get_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", "root", "leisure");
        /* Connect to the MySQL test database */
        con->setSchema("camera_xxtrinsics");

        pstmt = con->prepareStatement(ss.c_str());
        pstmt->setString(1,cuuid);
        pstmt->setString(2,cmatrix);
        pstmt->setString(3,ctype);
        pstmt->setString(4,cmatrix);
        pstmt->setString(5,ctype);
        pstmt->executeUpdate();

        //stmt = con->createStatement();
        //res = stmt->executeQuery(s.c_str());
        // delete res;
        // delete stmt;
        // delete con;
    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
    return true;
}
