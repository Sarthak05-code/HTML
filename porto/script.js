// Mobile nav toggle
const toggle = document.getElementById('menu-toggle');
const mobileNav = document.getElementById('mobile-nav');

toggle.addEventListener('click', () => {
    mobileNav.classList.toggle('hidden');
    mobileNav.classList.toggle('flex');
});

// Close mobile nav when a link is clicked
mobileNav.querySelectorAll('a').forEach(link => {
    link.addEventListener('click', () => {
        mobileNav.classList.add('hidden');
        mobileNav.classList.remove('flex');
    });
});

// Typing effect
const words = ["C dev", "Python dev", "C++ dev", "Bash user", "Aspiring ML dev"];
const typedEl = document.getElementById('typed');
let wordIndex = 0;
let charIndex = 0;
let deleting = false;

function type() {
    const current = words[wordIndex];

    if (!deleting) {
        charIndex++;
        typedEl.textContent = current.slice(0, charIndex);
        if (charIndex === current.length) {
            deleting = true;
            setTimeout(type, 1400);
            return;
        }
    } else {
        charIndex--;
        typedEl.textContent = current.slice(0, charIndex);
        if (charIndex === 0) {
            deleting = false;
            wordIndex = (wordIndex + 1) % words.length;
        }
    }

    setTimeout(type, deleting ? 50 : 90);
}

type();