
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Network {
    vector<string> devices;
    vector<vector<int>> adj;

    int findDevice(const string& name) {
        for (int i = 0; i < (int)devices.size(); i++) {
            if (devices[i] == name)
                return i;
        }
        return -1;
    }

    void DFS(int node, vector<bool>& visited) {
        visited[node] = true;
        cout << devices[node] << " ";

        for (int neighbour : adj[node]) {
            if (!visited[neighbour])
                DFS(neighbour, visited);
        }
    }

    bool findPath(int current, int destination,
                  vector<bool>& visited) {
        if (current == destination)
            return true;

        visited[current] = true;

        for (int neighbour : adj[current]) {
            if (!visited[neighbour]) {
                if (findPath(neighbour, destination, visited))
                    return true;
            }
        }
        return false;
    }

public:
    void addDevice(const string& name) {
        if (findDevice(name) != -1) {
            cout << "Device already exists!\n";
            return;
        }

        devices.push_back(name);
        adj.push_back(vector<int>());
        cout << "Device added successfully!\n";
    }

    void addConnection(const string& a, const string& b) {
        int u = findDevice(a);
        int v = findDevice(b);

        if (u == -1 || v == -1) {
            cout << "Device not found!\n";
            return;
        }

        if (u == v) {
            cout << "A device cannot be connected to itself!\n";
            return;
        }

        for (int x : adj[u]) {
            if (x == v) {
                cout << "Connection already exists!\n";
                return;
            }
        }

        adj[u].push_back(v);
        adj[v].push_back(u);
        cout << "Connection added successfully!\n";
    }

    void displayNetwork() {
        if (devices.empty()) {
            cout << "The network is empty.\n";
            return;
        }

        cout << "\nNetwork Connections:\n";

        for (int i = 0; i < (int)devices.size(); i++) {
            cout << devices[i] << " -> ";

            for (int neighbour : adj[i])
                cout << devices[neighbour] << " ";

            cout << "\n";
        }
    }

    void performDFS(const string& name) {
        int start = findDevice(name);

        if (start == -1) {
            cout << "Device not found!\n";
            return;
        }

        vector<bool> visited(devices.size(), false);

        cout << "DFS Traversal: ";
        DFS(start, visited);
        cout << "\n";
    }

    void checkConnection(const string& a, const string& b) {
        int u = findDevice(a);
        int v = findDevice(b);

        if (u == -1 || v == -1) {
            cout << "Device not found!\n";
            return;
        }

        vector<bool> visited(devices.size(), false);

        if (findPath(u, v, visited))
            cout << "A path exists between the devices.\n";
        else
            cout << "No path exists between the devices.\n";
    }
};

int main() {
    Network network;
    int choice;
    string a, b;

    do {
        cout << "\n===== NETWORK CONNECTION ANALYZER =====\n";
        cout << "1. Add Device\n";
        cout << "2. Add Connection\n";
        cout << "3. Display Network\n";
        cout << "4. Perform DFS Traversal\n";
        cout << "5. Check Connection Between Devices\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";

        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter device name: ";
                cin >> a;
                network.addDevice(a);
                break;

            case 2:
                cout << "Enter first device: ";
                cin >> a;
                cout << "Enter second device: ";
                cin >> b;
                network.addConnection(a, b);
                break;

            case 3:
                network.displayNetwork();
                break;

            case 4:
                cout << "Enter starting device: ";
                cin >> a;
                network.performDFS(a);
                break;

            case 5:
                cout << "Enter first device: ";
                cin >> a;
                cout << "Enter second device: ";
                cin >> b;
                network.checkConnection(a, b);
                break;

            case 6:
                cout << "Exiting program...\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 6);

    return 0;
}

