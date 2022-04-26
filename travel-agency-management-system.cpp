

#include<iostream>
#include<cstdio>
#include<fstream>
#include<sstream>
#include<string>
#include<cstdlib>
#include<conio.h>
#include<windows.h>
#include<mysql.h>
using namespace std;

// Global Variable
int qstate;
MYSQL* conn;
MYSQL_ROW row;
MYSQL_RES* res;
// Global Variable End

class db_response
{
public:
    static void ConnectionFunction()
    {
        conn = mysql_init(0);
        if (conn)
        {
            cout << "Database Connected" << endl;
            cout << "Press any key to continue..." << endl;
            //getch();
            system("cls");
        }
        else
            cout << "Failed To Connect!" << mysql_errno(conn) << endl;
        conn = mysql_real_connect(conn, "localhost", "root", "", "cpp_travelagency_db", 0, NULL, 0);
        if (conn)
        {
            cout << "Database Connected To MySql" << conn << endl;
            cout << "Press any key to continue..." << endl;
            //getch();
            system("cls");
        }
        else
            cout << "Failed To Connect!" << mysql_errno(conn) << endl;
    }
};

// Functions
void NewTravelTrip();
void ShowUsers();
void FindUser();
void EditUser();
void DeleteUser();
void AddTrip();
void EditTrip();
void DeleteTrip();
// Functions End

int main()
{
    // Initial Load
    system("cls");
    system("title Travel Agency Management System Program");
    system("color 0f");
    // Initial Load End

    // Call Methods
    db_response::ConnectionFunction();
    // Call Methods End

    // Variables
    int chooseOneFromMenu = 0;
    char exitSurity;
    // Variables End

    cout << "Welcome To Travel Agency Management System" << endl << endl;
    cout << "Travel Agency Management Menu" << endl;
    cout << "1. New Travel Trip." << endl;
    cout << "2. Show Users." << endl;
    cout << "3. Find User." << endl;
    cout << "4. Edit User." << endl;
    cout << "5. Delete User." << endl;
    cout << "6. Add Trip." << endl;
    cout << "7. Edit Trip." << endl;
    cout << "8. Delete Trip." << endl;
    cout << "9. Exit." << endl;
    cout << "Choose One: ";
    cin >> chooseOneFromMenu;

    switch (chooseOneFromMenu)
    {
    case 1:
        NewTravelTrip();
        break;
    case 2:
        ShowUsers();
        break;
    case 3:
        FindUser();
        break;
    case 4:
        EditUser();
        break;
    case 5:
        DeleteUser();
        break;
    case 6:
        AddTrip();
        break;
    case 7:
        EditTrip();
        break;
    case 8:
        DeleteTrip();
        break;
    case 9:
        ExitProgram:
        cout << "Program terminating. Are you sure? (y/N): ";
        cin >> exitSurity;
        if (exitSurity == 'y' || exitSurity == 'Y') {
            return 0;
        }else if (exitSurity == 'n' || exitSurity == 'N') {
            system("cls");
            main();
        }else {
            cout << "Next time choose after read the corresponding line." << endl;
            goto ExitProgram;
        }
        break;
    default:
        cout << "Please choose between 1 - 7. Press Enter To Continue...";
        getch();
        system("cls");
        main();
        break;
    }
    return 0;
}

// Functions
void NewTravelTrip()
{
    // Initial Load
    system("cls");
    // Initial Load End

    // Variables
    string userName = "";
    string userAddress = "";
    string userPhone = "";
    string userEmail = "";
    string userTripDate = "";
    string userTripPlanId = "";
    string userTripPlan = "";
    string userTripCost = "";
    char choose;
    // Variables End

    // Store Variables
    string storeUserTripPlan[500][500];
    int storeIndex1 = 0, storeIndex2 = 0;
    // Store Variables End

    cout << "Welcome To Travel Agency Management System" << endl << endl;
    cout << "New Travel Trip Menu" << endl << endl;

    cin.ignore(1, '\n');
    cout << "Enter User Name: ";
    getline(cin, userName);
    cout << "Enter User Address: ";
    getline(cin, userAddress);
    cout << "Enter Phone No.: ";
    getline(cin, userPhone);
    cout << "Enter Email: ";
    getline(cin, userEmail);
    cout << "Enter Trip Date: ";
    getline(cin, userTripDate);
    qstate = mysql_query(conn, "select * from travelagencytrips_tb");
    if (!qstate)
    {
        res = mysql_store_result(conn);
        printf("---------------------------------------------------------\n");
        printf("| %-10s | %-40s |\n", "Trip Id", "Trip Name");
        while ((row = mysql_fetch_row(res)))
        {
            printf("| %-10s | %-40s |\n", row[0], row[1]);
            storeUserTripPlan[storeIndex1][storeIndex2] = row[0];
            storeIndex2++;
            storeUserTripPlan[storeIndex1][storeIndex2] = row[1];
            storeIndex1++;storeIndex2--;
        }
        printf("---------------------------------------------------------\n");
}
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }
    cout << "Enter Trip Id: ";
    getline(cin, userTripPlanId);
    for (int i = 0, j = 0, k = 1; i < storeIndex1; i++)
    {
        if (storeUserTripPlan[i][j] == userTripPlanId)
        {
            userTripPlan = storeUserTripPlan[i][k];
            break;
        }
    }
    cout << "Enter Trip Cost: ";
    getline(cin, userTripCost);

    string insert_query = "insert into travelagency_tb (t_username, t_useraddress, t_userphone, t_useremail, t_usertripdate, t_usertripplan, t_usertripcost) values ('"+userName+"','"+userAddress+"','"+userPhone+"','"+userEmail+"','"+userTripDate+"','"+userTripPlan+"','"+userTripCost+"')";

    const char* q = insert_query.c_str(); // c_str converts string to constant char and this is required

    qstate = mysql_query(conn, q);

    if (!qstate)
    {
        cout << endl << "Successfully added in database." << endl;
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    // Exit Code
    cout << "Press 'm' to Menu and 'a' to Insert Again Or Any Other key to exit: ";
    cin >> choose;
    if (choose == 'm' || choose == 'M')
    {
        main();
    }
    else if (choose == 'a' || choose == 'A')
    {
        NewTravelTrip();
    }
    else
    {
        exit(0);
    }

}

void ShowUsers()
{
    // Initial Load
    system("cls");
    // Initial Load End

    // Variables
    char choose;
    // Variables End

    cout << "Welcome To Travel Agency Management System" << endl << endl;
    cout << "Show Users Menu" << endl << endl;

    qstate = mysql_query(conn, "select * from travelagency_tb");
    if (!qstate)
    {
        res = mysql_store_result(conn);
        while ((row = mysql_fetch_row(res)))
        {
            cout << "User Name: " << row[1] << "\nUser Address: " << row[2] << "\nUser Phone: " << row[3] << "\nUser Email: " << row[4] << "\nTrip Date: " << row[5] << "\nTrip Plan: " << row[6] << "\nTrip Cost: " << row[7] << endl << endl;
        }
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    // Exit Code
    ExitMenu:
    cout << "Press 'm' to Menu and any other key to Exit: ";
    cin >> choose;
    if (choose == 'm' || choose == 'M')
    {
        main();
    }
    else
    {
        exit(0);
    }
}

void FindUser()
{
    // Initial Load
    system("cls");
    // Initial Load End

    // Variables
    string input = "";
    char choose;
    // Variables End

    cout << "Welcome To Travel Agency Management System" << endl << endl;
    cout << "Show Users Menu" << endl << endl;

    cin.ignore(1, '\n');
    cout << "Enter User Name: ";
    getline(cin, input);
    string findbyname_query = "select * from travelagency_tb where t_username like '%"+input+"%'";
    const char* qn = findbyname_query.c_str();
    qstate = mysql_query(conn, qn);

    cout << endl;
    if (!qstate)
    {
        res = mysql_store_result(conn);
        while ((row = mysql_fetch_row(res)))
        {
            cout << "User Name: " << row[1] << "\nUser Address: " << row[2] << "\nUser Phone: " << row[3] << "\nUser Email: " << row[4] << "\nTrip Date: " << row[5] << "\nTrip Plan: " << row[6] << "\nTrip Cost: " << row[7] << endl << endl;
        }
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    ExitMenu:
    cout << "Press 'm' to Menu, 'a' to Search again and any other key to Exit: ";
    cin >> choose;
    if (choose == 'm' || choose == 'M')
    {
        main();
    }
    else if (choose == 'a' || choose == 'A')
    {
        FindUser();
    }
    else
    {
        exit(0);
    }
}

void EditUser()
{
    system("cls");

    // Variables
    string userName = "";
    string userAddress = "";
    string userPhone = "";
    string userEmail = "";
    string userTripDate = "";
    string userTripPlanId = "";
    string userTripPlan = "";
    string userTripCost = "";
    string items[5000];
    char choose;
    int itemId;
    bool HaveException = false;
    bool NotInDatabase = false;
    int indexForId = 0;

    // Store Variables
    string storeColumnId = "";
    string storeUserName = "";
    string storeUserAddress = "";
    string storeUserPhone = "";
    string storeUserEmail = "";
    string storeUserTripDate = "";
    string storeUserTripPlanId = "";
    string storeUserTripPlan = "";
    string storeUserTripCost = "";
    string storeUserTripPlan2d[500][500];
    int storeIndex1 = 0, storeIndex2 = 0;
    // Variables End

    cout << "Welcome To Student Fee Inquiry Program" << endl << endl;
    cout << "Edit Student Record" << endl;


    qstate = mysql_query(conn, "select * from travelagency_tb");
    if (!qstate)
    {
        res = mysql_store_result(conn);
        printf("-----------------------------------------------------------------------------------------------------------------\n");
        printf("| %-10s | %-25s | %-25s | %-40s |\n", "Column ID", "User Name", "Trip Date", "Trip Plan");
        while ((row = mysql_fetch_row(res)))
        {
            printf("| %-10s | %-25s | %-25s | %-40s |\n", row[0], row[1], row[5], row[6]);
        }
        printf("-----------------------------------------------------------------------------------------------------------------\n");
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    try
    {
        cout << endl;
        cout << "Enter Item Column ID: ";
        cin >> itemId;
        cout << endl;
    }
    catch (exception e)
    {
        cout << "Please Enter a valid NUMBER." << endl;
        HaveException = true;
        goto ExitMenu;
    }

    if (HaveException == false)
    {
        stringstream streamid;
        string strid;
        streamid << itemId;
        streamid >> strid;

        for (int i = 0; i < indexForId; i++)
        {
            if (strid != items[i])
            {
                NotInDatabase = true;
            }else
            {
                NotInDatabase = false;
                break;
            }
        }

        if (NotInDatabase == false)
        {
            string findbyid_query = "select * from travelagency_tb where t_id = '"+strid+"'";
            const char* qi = findbyid_query.c_str();
            qstate = mysql_query(conn, qi);

            if (!qstate)
            {
                cout << endl;

                res = mysql_store_result(conn);
                while ((row = mysql_fetch_row(res)))
                {
                    cout << "User Name: " << row[1] << "\nUser Address: " << row[2] << "\nUser Phone: " << row[3] << "\nUser Email: " << row[4] << "\nTrip Date: " << row[5] << "\nTrip Plan: " << row[6] << "\nTrip Cost: " << row[7] << endl << endl;
                    storeColumnId = row[0];
                    storeUserName = row[1];
                    storeUserAddress = row[2];
                    storeUserPhone = row[3];
                    storeUserEmail = row[4];
                    storeUserTripDate = row[5];
                    storeUserTripPlan = row[6];
                    storeUserTripCost = row[7];
                }
            }
            else
            {
                cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            }

            cin.ignore(1, '\n');
            cout << "Enter User Name (X to not change): ";
            getline(cin, userName);
            if (userName == "X")
            {
                userName = storeUserName;
            }
            cout << "Enter User Address (X to not change): ";
            getline(cin, userAddress);
            if (userAddress == "X")
            {
                userAddress = storeUserAddress;
            }
            cout << "Enter User Phone No. (X to not change): ";
            getline(cin, userPhone);
            if (userPhone == "X")
            {
                userPhone = storeUserPhone;
            }
            cout << "Enter User Email (X to not change): ";
            getline(cin, userEmail);
            if (userEmail == "X")
            {
                userEmail = storeUserEmail;
            }
            cout << "Enter User Trip Date (X to not change): ";
            cin >> userTripDate;
            if (userTripDate == "X")
            {
                userTripDate = storeUserTripDate;
            }

            qstate = mysql_query(conn, "select * from travelagencytrips_tb");
            if (!qstate)
            {
                res = mysql_store_result(conn);
                printf("---------------------------------------------------------\n");
                printf("| %-10s | %-40s |\n", "Trip Id", "Trip Name");
                while ((row = mysql_fetch_row(res)))
                {
                    printf("| %-10s | %-40s |\n", row[0], row[1]);
                    storeUserTripPlan2d[storeIndex1][storeIndex2] = row[0];
                    storeIndex2++;
                    storeUserTripPlan2d[storeIndex1][storeIndex2] = row[1];
                    storeIndex1++;storeIndex2--;
                }
                printf("---------------------------------------------------------\n");
            }
            else
            {
                cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            }
            cin.ignore(1, '\n');
            cout << "Enter Trip Id (X to not change): ";
            getline(cin, userTripPlanId);
            if (userTripPlanId == "X")
            {
                userTripPlan = storeUserTripPlan;
            }
            else
            {
                for (int i = 0, j = 0, k = 1; i < storeIndex1; i++)
                {
                    if (storeUserTripPlan2d[i][j] == userTripPlanId)
                    {
                        userTripPlan = storeUserTripPlan2d[i][k];
                        break;
                    }
                }
            }

            cout << "Enter Trip Cost (X to not change): ";
            getline(cin, userTripCost);
            if (userTripCost == "X")
            {
                userTripCost = storeUserTripCost;
            }

            string update_query = "update travelagency_tb set t_username = '"+userName+"', t_useraddress = '"+userAddress+"', t_userphone = '"+userPhone+"', t_useremail = '"+userEmail+"', t_usertripdate = '"+userTripDate+"', t_usertripplan = '"+userTripPlan+"', t_usertripcost = '"+userTripCost+"' where t_id = '"+strid+"'";
            const char* qu = update_query.c_str();
            qstate = mysql_query(conn, qu);

            if (!qstate)
            {
                cout << endl << "Successfully Saved In Database." << endl;
            }
            else
            {
                cout << "Failed To Update!" << mysql_errno(conn) << endl;
            }

        }
        else
        {
            cout << "Item Not Found in database." << endl;
        }
    }

    ExitMenu:
    cout << "Press 'm' to Menu, 'e' to edit another item and any other key to Exit: ";
    cin >> choose;
    if (choose == 'm' || choose == 'M')
    {
        main();
    }
    else if (choose == 'e' || choose == 'E')
    {
        EditUser();
    }
    else
    {
        exit(0);
    }
}

void DeleteUser()
{
    system("cls");

    // Variables
    char choose;
    int itemId;
    string items[5000];
    int indexForId = 0;
    bool HaveException = false, NotInDatabase = false;
    // Variables End

    cout << "Welcome To Travel Agency Management System" << endl << endl;
    cout << "Show Users Menu" << endl << endl;


    qstate = mysql_query(conn, "select * from travelagency_tb");
    if (!qstate)
    {
        res = mysql_store_result(conn);
        printf("-----------------------------------------------------------------------------------------------------------------\n");
        printf("| %-10s | %-25s | %-25s | %-40s |\n", "Column ID", "User Name", "Trip Date", "Trip Plan");
        while ((row = mysql_fetch_row(res)))
        {
            printf("| %-10s | %-25s | %-25s | %-40s |\n", row[0], row[1], row[5], row[6]);
            items[indexForId] = row[0];
            indexForId++;
        }
        printf("-----------------------------------------------------------------------------------------------------------------\n");
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    try
    {
        cout << endl;
        cout << "Enter Item Column ID: ";
        cin >> itemId;
        cout << endl;
    }
    catch (exception e)
    {
        cout << "Please Enter a valid NUMBER." << endl;
        HaveException = true;
        goto ExitMenu;
    }

    if (HaveException == false)
    {
        stringstream streamid;
        string strid;
        streamid << itemId;
        streamid >> strid;

        for (int i = 0; i < indexForId; i++)
        {
            if (strid != items[i])
            {
                NotInDatabase = true;
            }else
            {
                NotInDatabase = false;
                break;
            }
        }

        if (NotInDatabase == false)
        {
            string delete_query = "delete from travelagency_tb where t_id = '"+strid+"'";
            const char* qd = delete_query.c_str();
            qstate = mysql_query(conn, qd);

            if (!qstate)
            {
                cout << "Successfully Deleted From Database." << endl;
            }
            else
            {
                cout << "Failed To Delete!" << mysql_errno(conn) << endl;
            }

        }
        else
        {
            cout << "Item Not Found in database." << endl;
        }
    }

    // Exit Code
    ExitMenu:
    cout << "Press 'm' to Menu, 'd' to delete another record and any other key to Exit: ";
    cin >> choose;
    if (choose == 'm' || choose == 'M')
    {
        main();
    }
    else if (choose == 'd' || choose == 'D')
    {
        DeleteUser();
    }
    else
    {
        exit(0);
    }
}

void AddTrip()
{
    // Initial Load
    system("cls");
    // Initial Load End

    // Variables
    string tripName = "";
    char choose;
    // Variables End

    cout << "Welcome To Travel Agency Management System" << endl << endl;
    cout << "Add Trip Menu" << endl << endl;

    cin.ignore(1, '\n');
    cout << "Enter Trip Name: ";
    getline(cin, tripName);

    string insert_query = "insert into travelagencytrips_tb (t_trip) values ('"+tripName+"')";

    const char* q = insert_query.c_str(); // c_str converts string to constant char and this is required

    qstate = mysql_query(conn, q);

    if (!qstate)
    {
        cout << endl << "Successfully added in database." << endl;
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    qstate = mysql_query(conn, "select * from travelagencytrips_tb");
    if (!qstate)
    {
        res = mysql_store_result(conn);
        printf("---------------------------------------------------------\n");
        printf("| %-10s | %-40s |\n", "Trip Id", "Trip Name");
        while ((row = mysql_fetch_row(res)))
        {
            printf("| %-10s | %-40s |\n", row[0], row[1]);
        }
        printf("---------------------------------------------------------\n");
}
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    // Exit Code
    cout << "Press 'm' to Menu and 'a' to Insert Again Or Any Other key to exit: ";
    cin >> choose;
    if (choose == 'm' || choose == 'M')
    {
        main();
    }
    else if (choose == 'a' || choose == 'A')
    {
        AddTrip();
    }
    else
    {
        exit(0);
    }
}

void EditTrip()
{
    system("cls");

    // Variables
    string tripName = "";
    string items[5000];
    char choose;
    int itemId;
    bool HaveException = false;
    bool NotInDatabase = false;
    int indexForId = 0;

    // Store Variables
    string storeColumnId = "";
    string storeTripName = "";
    // Variables End

    cout << "Welcome To Student Fee Inquiry Program" << endl << endl;
    cout << "Edit Trip Record" << endl;


    qstate = mysql_query(conn, "select * from travelagencytrips_tb");
    if (!qstate)
    {
        res = mysql_store_result(conn);
        printf("---------------------------------------------------------\n");
        printf("| %-10s | %-40s |\n", "Trip Id", "Trip Name");
        while ((row = mysql_fetch_row(res)))
        {
            printf("| %-10s | %-40s |\n", row[0], row[1]);
        }
        printf("---------------------------------------------------------\n");
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    try
    {
        cout << endl;
        cout << "Enter Item Column ID: ";
        cin >> itemId;
        cout << endl;
    }
    catch (exception e)
    {
        cout << "Please Enter a valid NUMBER." << endl;
        HaveException = true;
        goto ExitMenu;
    }

    if (HaveException == false)
    {
        stringstream streamid;
        string strid;
        streamid << itemId;
        streamid >> strid;

        for (int i = 0; i < indexForId; i++)
        {
            if (strid != items[i])
            {
                NotInDatabase = true;
            }else
            {
                NotInDatabase = false;
                break;
            }
        }

        if (NotInDatabase == false)
        {
            string findbyid_query = "select * from travelagencytrips_tb where t_id = '"+strid+"'";
            const char* qi = findbyid_query.c_str();
            qstate = mysql_query(conn, qi);

            if (!qstate)
            {
                cout << endl;
                res = mysql_store_result(conn);
                printf("---------------------------------------------------------\n");
                printf("| %-10s | %-40s |\n", "Trip Id", "Trip Name");
                while ((row = mysql_fetch_row(res)))
                {
                    printf("| %-10s | %-40s |\n", row[0], row[1]);
                }
                printf("---------------------------------------------------------\n");
            }
            else
            {
                cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            }

            cin.ignore(1, '\n');
            cout << "Enter Trip Name (xN to not change): ";
            getline(cin, tripName);
            if (tripName == "xN")
            {
                tripName = storeTripName;
            }

            string update_query = "update travelagencytrips_tb set t_trip = '"+tripName+"' where t_id = '"+strid+"'";
            const char* qu = update_query.c_str();
            qstate = mysql_query(conn, qu);

            if (!qstate)
            {
                cout << endl << "Successfully Saved In Database." << endl;
            }
            else
            {
                cout << "Failed To Update!" << mysql_errno(conn) << endl;
            }

        }
        else
        {
            cout << "Item Not Found in database." << endl;
        }
    }

    ExitMenu:
    cout << "Press 'm' to Menu, 'e' to edit another item and any other key to Exit: ";
    cin >> choose;
    if (choose == 'm' || choose == 'M')
    {
        main();
    }
    else if (choose == 'e' || choose == 'E')
    {
        EditTrip();
    }
    else
    {
        exit(0);
    }
}

void DeleteTrip()
{
    system("cls");

    // Variables
    char choose;
    int itemId;
    string items[5000];
    int indexForId = 0;
    bool HaveException = false, NotInDatabase = false;
    // Variables End

    cout << "Welcome To Travel Agency Management System" << endl << endl;
    cout << "Delete User Menu" << endl << endl;


    qstate = mysql_query(conn, "select * from travelagencytrips_tb");
    if (!qstate)
    {
        res = mysql_store_result(conn);
        printf("---------------------------------------------------------\n");
        printf("| %-10s | %-40s |\n", "Trip ID", "Trip Name");
        while ((row = mysql_fetch_row(res)))
        {
            printf("| %-10s | %-40s |\n", row[0], row[1]);
            items[indexForId] = row[0];
            indexForId++;
        }
        printf("---------------------------------------------------------\n");
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    try
    {
        cout << endl;
        cout << "Enter Item Column ID: ";
        cin >> itemId;
        cout << endl;
    }
    catch (exception e)
    {
        cout << "Please Enter a valid NUMBER." << endl;
        HaveException = true;
        goto ExitMenu;
    }

    if (HaveException == false)
    {
        stringstream streamid;
        string strid;
        streamid << itemId;
        streamid >> strid;

        for (int i = 0; i < indexForId; i++)
        {
            if (strid != items[i])
            {
                NotInDatabase = true;
            }else
            {
                NotInDatabase = false;
                break;
            }
        }

        if (NotInDatabase == false)
        {
            string delete_query = "delete from travelagencytrips_tb where t_id = '"+strid+"'";
            const char* qd = delete_query.c_str();
            qstate = mysql_query(conn, qd);

            if (!qstate)
            {
                cout << "Successfully Deleted From Database." << endl;
            }
            else
            {
                cout << "Failed To Delete!" << mysql_errno(conn) << endl;
            }

        }
        else
        {
            cout << "Item Not Found in database." << endl;
        }
    }

    // Exit Code
    ExitMenu:
    cout << "Press 'm' to Menu, 'd' to delete another record and any other key to Exit: ";
    cin >> choose;
    if (choose == 'm' || choose == 'M')
    {
        main();
    }
    else if (choose == 'd' || choose == 'D')
    {
        DeleteUser();
    }
    else
    {
        exit(0);
    }
}
