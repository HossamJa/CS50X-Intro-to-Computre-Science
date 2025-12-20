// Home page Scripts
const bootLines = [
    "> Initializing Engineering Portfolio...",
    "> Loading Physics & Analytical Modules... OK",
    "> Checking Business & Marketing Logic... OK",
    "> Establishing Cloud Infrastructure... OK",
    "> Verifying 45+ Certifications... OK",
    "> Deploying 25+ Project Repositories... OK",
    "> MISSION READY. Accessing Interface..."
];

const bootContainer = document.getElementById('boot-text');
const profile = document.getElementById('profile-content');
let lineIndex = 0;

function typeBoot() {
    if (lineIndex < bootLines.length) {
        let p = document.createElement('p');
        p.classList.add('mb-1');
        p.innerHTML = bootLines[lineIndex];
        bootContainer.appendChild(p);
        lineIndex++;
        setTimeout(typeBoot, 600); // Speed of the boot sequence
    } else {
        // Hide terminal and show profile after 1 second delay
        setTimeout(() => {
            document.getElementById('terminal-boot').classList.add('d-none');
            profile.classList.remove('d-none');
            profile.classList.add('fade-in'); // Add a CSS transition if you like
        }, 1000);
    }
}

// Start the sequence on load
window.onload = typeBoot;

// Archive Scripts

// Function to filter by button click
function filterCerts(category) {
    const cards = document.querySelectorAll('.cert-card');
    
    cards.forEach(card => {
        if (category === 'all' || card.getAttribute('data-category') === category) {
            card.style.display = 'block';
        } else {
            card.style.display = 'none';
        }
    });
}

// Function to filter by typing in the search bar
document.getElementById('certSearch').addEventListener('keyup', function() {
    let searchValue = this.value.toLowerCase();
    let cards = document.querySelectorAll('.cert-card');

    cards.forEach(card => {
        let title = card.querySelector('.card-title').innerText.toLowerCase();
        if (title.includes(searchValue)) {
            card.style.display = 'block';
        } else {
            card.style.display = 'none';
        }
    });
});

// Lounchpad scripts
function filterMissions(type) {
    const cards = document.querySelectorAll('.mission-card');
    const buttons = document.querySelectorAll('#missionFilters .nav-link');

    // Update active button state
    buttons.forEach(btn => {
        btn.classList.remove('active');
        if(btn.innerText.toLowerCase().includes(type)) btn.classList.add('active');
    });

    cards.forEach(card => {
        // Add a small fade effect via JS classes
        if (type === 'all' || card.getAttribute('data-type') === type) {
            card.style.display = 'block';
            setTimeout(() => { card.style.opacity = '1'; }, 10);
        } else {
            card.style.opacity = '0';
            setTimeout(() => { card.style.display = 'none'; }, 300);
        }
    });
}

// Journey scripts

const logs = {
    physics: "In this era, I developed the scientific method approach to problem-solving. Physics taught me how to break complex systems down into their smallest components—a skill I use daily in debugging code and infrastructure.",
    marketing: "Learned the 'Business Side' of tech. Understanding SEO and SaaS metrics gave me a unique perspective on WHY we build software: to solve user problems and drive value. I don't just write code; I build products.",
    it: "The 'Front Lines.' This stage was about hardware specs, server racks, and hands-on IT support. It bridge the gap between abstract software and the physical machines that run it.",
    engineering: "The Final Orbit. Merging all previous stages into Engineering. CS50 provided the logic foundation, while my self-taught path in Cloud and DevOps provided the modern toolset to deploy at scale."
};

function showLog(stage) {
    const logBox = document.getElementById('missionLog');
    const logTitle = document.getElementById('logTitle');
    const logText = document.getElementById('logText');

    logBox.classList.remove('d-none');
    logTitle.innerText = `> MISSION_LOG: ${stage.toUpperCase()}`;
    logText.innerText = logs[stage];
    
    // Auto-scroll to log
    logBox.scrollIntoView({ behavior: 'smooth' });
}