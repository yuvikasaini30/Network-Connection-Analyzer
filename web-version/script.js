// Firebase configuration
const firebaseConfig = {
    apiKey: "AIzaSyA49yqqOo5W4J6nm2SNIsU3yEene_WnHSw",
    authDomain: "network-connection-analyzer.firebaseapp.com",
    projectId: "network-connection-analyzer",
    storageBucket: "network-connection-analyzer.firebasestorage.app",
    messagingSenderId: "107762431853",
    appId: "1:107762431853:web:221eefd1e5360f7fc94c64"
};

firebase.initializeApp(firebaseConfig);

const auth = firebase.auth();
const db = firebase.firestore();
const networkRef = db.collection("networks").doc("demo");

let cloudReady = false;
let firstCloudLoad = true;

// Restore the local browser backup first
const graph = new Map();

try {
    const saved = JSON.parse(
        localStorage.getItem("networkAnalyzerGraph") || "{}"
    );

    for (const [name, neighbors] of Object.entries(saved)) {
        graph.set(name, new Set(neighbors));
    }
} catch (error) {
    console.error("Could not restore saved network:", error);
}

const deviceName = document.getElementById("deviceName");
const connectFrom = document.getElementById("connectFrom");
const connectTo = document.getElementById("connectTo");
const pathFrom = document.getElementById("pathFrom");
const pathTo = document.getElementById("pathTo");
const result = document.getElementById("result");

function saveCloud() {
    if (!cloudReady) return;

    const savedGraph = {};

    for (const [name, neighbors] of graph) {
        savedGraph[name] = [...neighbors];
    }

    networkRef.set({
        graph: savedGraph,
        updatedAt: firebase.firestore.FieldValue.serverTimestamp()
    }).catch(error => {
        console.error("Cloud save failed:", error);
        result.textContent = "Cloud save failed. Check your connection.";
    });
}

function addDevice() {
    const name = deviceName.value.trim();

    if (!name) {
        result.textContent = "Please enter a device name.";
        return;
    }

    if (graph.has(name)) {
        result.textContent = "This device already exists.";
        return;
    }

    graph.set(name, new Set());
    deviceName.value = "";
    update();
    result.textContent = `Device "${name}" added successfully.`;
}

function connectDevices() {
    const a = connectFrom.value;
    const b = connectTo.value;

    if (!a || !b) {
        result.textContent = "Please select both devices.";
        return;
    }

    if (a === b) {
        result.textContent = "A device cannot be connected to itself.";
        return;
    }

    if (graph.get(a).has(b)) {
        result.textContent = "These devices are already connected.";
        return;
    }

    graph.get(a).add(b);
    graph.get(b).add(a);

    update();
    result.textContent = `Connected ${a} to ${b}.`;
}

function dfs(start) {
    const visited = new Set();
    const order = [];

    function visit(node) {
        visited.add(node);
        order.push(node);

        for (const neighbor of graph.get(node)) {
            if (!visited.has(neighbor)) {
                visit(neighbor);
            }
        }
    }

    visit(start);
    return order;
}

function checkPath() {
    const start = pathFrom.value;
    const end = pathTo.value;

    if (!start || !end) {
        result.textContent =
            "Please select a starting and destination device.";
        return;
    }

    if (start === end) {
        result.textContent = `A path exists: ${start}`;
        return;
    }

    const visited = new Set();
    const parent = new Map();
    const queue = [start];

    visited.add(start);

    while (queue.length) {
        const current = queue.shift();

        if (current === end) break;

        for (const neighbor of graph.get(current)) {
            if (!visited.has(neighbor)) {
                visited.add(neighbor);
                parent.set(neighbor, current);
                queue.push(neighbor);
            }
        }
    }

    if (!visited.has(end)) {
        result.textContent =
            `No path exists between ${start} and ${end}.`;
        return;
    }

    const route = [];
    let current = end;

    while (current !== undefined) {
        route.unshift(current);
        current = parent.get(current);
    }

    result.textContent =
        `A path exists! Route: ${route.join(" → ")}`;
}

function resetNetwork() {
    graph.clear();
    update();
    result.textContent = "Network has been reset.";
}

function updateSelect(select, placeholder) {
    const previous = select.value;
    select.innerHTML = "";

    const first = document.createElement("option");
    first.value = "";
    first.textContent = placeholder;
    select.appendChild(first);

    for (const name of graph.keys()) {
        const option = document.createElement("option");
        option.value = name;
        option.textContent = name;
        select.appendChild(option);
    }

    if (graph.has(previous)) {
        select.value = previous;
    }
}

function drawGraph() {
    const container = document.getElementById("graph");
    container.innerHTML = "";

    const names = [...graph.keys()];
    const width = Math.max(container.clientWidth, 300);
    const height = 250;
    const centerX = width / 2;
    const centerY = height / 2;
    const radius = Math.min(width * 0.30, 65);

    if (names.length === 0) {
        const message = document.createElement("p");
        message.className = "empty-message";
        message.textContent = "Add devices to build your network.";
        container.appendChild(message);
        return;
    }

    const svgNS = "http://www.w3.org/2000/svg";
    const svg = document.createElementNS(svgNS, "svg");

    svg.setAttribute("width", "100%");
    svg.setAttribute("height", height);
    svg.setAttribute("viewBox", `0 0 ${width} ${height}`);

    const positions = new Map();

    names.forEach((name, index) => {
        const angle =
            (2 * Math.PI * index / names.length) - Math.PI / 2;

        positions.set(name, {
            x: centerX + radius * Math.cos(angle),
            y: centerY + radius * Math.sin(angle)
        });
    });

    for (const [name, neighbors] of graph) {
        for (const neighbor of neighbors) {
            if (names.indexOf(name) < names.indexOf(neighbor)) {
                const a = positions.get(name);
                const b = positions.get(neighbor);
                const line = document.createElementNS(svgNS, "line");

                line.setAttribute("x1", a.x);
                line.setAttribute("y1", a.y);
                line.setAttribute("x2", b.x);
                line.setAttribute("y2", b.y);
                line.setAttribute("stroke", "#38bdf8");
                line.setAttribute("stroke-width", "2");

                svg.appendChild(line);
            }
        }
    }

    for (const name of names) {
        const point = positions.get(name);
        const circle = document.createElementNS(svgNS, "circle");

        circle.setAttribute("cx", point.x);
        circle.setAttribute("cy", point.y);
        circle.setAttribute("r", "25");
        circle.setAttribute("fill", "#075985");
        circle.setAttribute("stroke", "#38bdf8");
        circle.setAttribute("stroke-width", "2");

        svg.appendChild(circle);

        const label = document.createElementNS(svgNS, "text");

        label.setAttribute("x", point.x);
        label.setAttribute("y", point.y + 42);
        label.setAttribute("fill", "#e5e7eb");
        label.setAttribute("font-size", "12");
        label.setAttribute("text-anchor", "middle");

        label.textContent =
            name.length > 15 ? name.slice(0, 13) + "…" : name;

        svg.appendChild(label);
    }

    container.appendChild(svg);
}

function update(saveToCloud = true) {
    updateSelect(connectFrom, "Select first device");
    updateSelect(connectTo, "Select second device");
    updateSelect(pathFrom, "Path: starting device");
    updateSelect(pathTo, "Path: destination device");

    document.getElementById("deviceCount").textContent = graph.size;

    let connections = 0;

    for (const neighbors of graph.values()) {
        connections += neighbors.size;
    }

    connections /= 2;

    document.getElementById("connectionCount").textContent = connections;

    document.getElementById("networkStatus").textContent =
        graph.size === 0 ? "Empty" : "Active";

    drawGraph();

    const saved = {};

    for (const [name, neighbors] of graph) {
        saved[name] = [...neighbors];
    }

    localStorage.setItem(
        "networkAnalyzerGraph",
        JSON.stringify(saved)
    );

    if (saveToCloud) {
        saveCloud();
    }
}

// Button events
document.getElementById("addDevice")
    .addEventListener("click", addDevice);

document.getElementById("connectDevices")
    .addEventListener("click", connectDevices);

document.getElementById("pathButton")
    .addEventListener("click", checkPath);

document.getElementById("resetButton")
    .addEventListener("click", resetNetwork);

document.getElementById("dfsButton").addEventListener("click", () => {
    const start = pathFrom.value || graph.keys().next().value;

    if (!start) {
        result.textContent = "Add a device first.";
        return;
    }

    result.textContent =
        `DFS Traversal: ${dfs(start).join(" → ")}`;
});

deviceName.addEventListener("keydown", event => {
    if (event.key === "Enter") addDevice();
});

window.addEventListener("resize", drawGraph);

// Initial display
update(false);

// Sign in anonymously and listen for cloud changes
auth.signInAnonymously()
    .then(() => {
        networkRef.onSnapshot(doc => {
            if (doc.exists) {
                const cloudGraph = doc.data().graph || {};

                graph.clear();

                for (const [name, neighbors] of Object.entries(cloudGraph)) {
                    graph.set(name, new Set(neighbors));
                }

                cloudReady = true;
                update(false);

                if (firstCloudLoad) {
                    result.textContent = "Connected to cloud successfully.";
                }
            } else {
                cloudReady = true;
                saveCloud();

                if (firstCloudLoad) {
                    result.textContent =
                        "Cloud connected. Your network is ready to save.";
                }
            }

            firstCloudLoad = false;
        }, error => {
            console.error("Cloud sync error:", error);
            result.textContent = "Cloud sync error. Please check Firebase.";
        });
    })
    .catch(error => {
        console.error("Authentication error:", error);
        result.textContent =
            "Could not connect to cloud. Please check Firebase Authentication.";
    });
