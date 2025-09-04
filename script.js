document.addEventListener('DOMContentLoaded', () => {
    // This array mirrors the 'vector<Book> books;' in your C++ code.
    let library = [];

    // --- DOM Element References ---
    const addBookForm = document.getElementById('addBookForm');
    const bookList = document.getElementById('bookList');
    const emptyMessage = document.getElementById('emptyMessage');
    const searchInput = document.getElementById('searchInput');
    const modal = document.getElementById('modal');
    const modalTitle = document.getElementById('modalTitle');
    const modalMessage = document.getElementById('modalMessage');
    const modalInput = document.getElementById('modalInput');
    const modalCancel = document.getElementById('modalCancel');
    const modalConfirm = document.getElementById('modalConfirm');
    
    let currentAction = null; // To handle confirmations in the modal

    // --- Modal Functions ---
    function showModal(title, message, showInput = false, action = null) {
        modalTitle.textContent = title;
        modalMessage.textContent = message;
        modalInput.style.display = showInput ? 'block' : 'none';
        modalInput.value = '';
        modal.classList.remove('hidden');
        currentAction = action;
    }
    modalCancel.addEventListener('click', () => modal.classList.add('hidden'));
    modalConfirm.addEventListener('click', () => {
        if (currentAction) currentAction();
        modal.classList.add('hidden');
    });

    // --- Core Library Functions (JavaScript version of your C++ Library class) ---

    /**
     * Renders the books to the DOM. This is the equivalent of your 'listAllBooks' function.
     */
    function renderBooks(booksToRender = library) {
        // Sort books by title, just like in your C++ code's listAllBooks function.
        booksToRender.sort((a, b) => a.title.localeCompare(b.title));

        bookList.innerHTML = '';
        emptyMessage.classList.toggle('hidden', library.length > 0);

        if (booksToRender.length === 0 && library.length > 0) {
             bookList.innerHTML = `<p class="text-center text-gray-500 py-16">No books match your search.</p>`;
        }

        booksToRender.forEach(book => {
            const statusClass = book.isIssued ? 'bg-red-100 text-red-800' : 'bg-green-100 text-green-800';
            const bookCard = `
                <div class="bg-gray-50 p-4 rounded-xl border border-gray-200 flex flex-col md:flex-row justify-between items-start md:items-center">
                    <div>
                        <h3 class="font-bold text-lg text-gray-800">${book.title}</h3>
                        <p class="text-gray-500 text-sm">by ${book.author} (ID: ${book.id})</p>
                    </div>
                    <div class="flex items-center space-x-2 mt-3 md:mt-0">
                        <span class="text-xs font-semibold px-3 py-1 rounded-full ${statusClass}">${book.isIssued ? 'Issued' : 'Available'}</span>
                        ${!book.isIssued ? `<button data-id="${book.id}" class="issue-btn px-3 py-1 bg-blue-500 text-white text-sm rounded-md hover:bg-blue-600">Issue</button>` : ''}
                        ${book.isIssued ? `<button data-id="${book.id}" class="return-btn px-3 py-1 bg-green-500 text-white text-sm rounded-md hover:bg-green-600">Return</button>` : ''}
                        <button data-id="${book.id}" class="delete-btn px-3 py-1 bg-gray-700 text-white text-sm rounded-md hover:bg-gray-800">Delete</button>
                    </div>
                </div>
            `;
            bookList.innerHTML += bookCard;
        });
    }
    
    /**
     * Handles adding a new book. This is the logic from your 'addBook' function.
     */
    addBookForm.addEventListener('submit', (e) => {
        e.preventDefault();
        const id = parseInt(document.getElementById('bookId').value);
        const title = document.getElementById('bookTitle').value.trim();
        const author = document.getElementById('bookAuthor').value.trim();

        if (isNaN(id) || !title || !author) {
            showModal('Error', 'Please fill in all fields correctly.');
            return;
        }
        if (library.some(book => book.id === id)) {
            showModal('Error', `A book with ID ${id} already exists.`);
            return;
        }
        library.push({ id, title, author, isIssued: false });
        showModal('Success', `Book "${title}" was added successfully.`);
        renderBooks();
        addBookForm.reset();
    });

    /**
     * This single event listener handles all button clicks inside the book list,
     * covering the logic for 'issueBook', 'returnBook', and 'deleteBook'.
     */
    bookList.addEventListener('click', (e) => {
        const target = e.target;
        const bookId = parseInt(target.dataset.id);
        if (isNaN(bookId)) return;

        const book = library.find(b => b.id === bookId);
        if (!book) return;

        if (target.classList.contains('delete-btn')) {
            showModal('Confirm Deletion', `Are you sure you want to delete "${book.title}"?`, false, () => {
                library = library.filter(b => b.id !== bookId);
                renderBooks();
            });
        } else if (target.classList.contains('issue-btn')) {
            showModal('Issue Book', `Enter student name for "${book.title}".`, true, () => {
                const studentName = modalInput.value.trim();
                if (studentName && book) {
                    book.isIssued = true;
                    showModal('Success', `Book issued to ${studentName}.`);
                    renderBooks();
                } else {
                    showModal('Error', 'Student name cannot be empty.');
                }
            });
        } else if (target.classList.contains('return-btn')) {
            showModal('Confirm Return', `Are you sure you want to return "${book.title}"?`, false, () => {
                if (book) {
                    book.isIssued = false;
                    renderBooks();
                }
            });
        }
    });

    /**
     * Handles real-time search, mirroring 'searchBookById' and 'searchBookByTitle'.
     */
    searchInput.addEventListener('input', (e) => {
        const searchTerm = e.target.value.toLowerCase();
        const filteredBooks = library.filter(book =>
            book.id.toString().includes(searchTerm) ||
            book.title.toLowerCase().includes(searchTerm)
        );
        renderBooks(filteredBooks);
    });

    // --- Initial Render ---
    // This displays the initial (empty) state of the library when the page loads.
    renderBooks();
});
