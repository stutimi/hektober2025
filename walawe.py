import json
import os

FILE_NAME = 'todo.json'

def load_tasks():
    """Memuat tugas dari file JSON."""
    if not os.path.exists(FILE_NAME):
        return []  # Kembalikan list kosong jika file tidak ada
    
    try:
        with open(FILE_NAME, 'r') as f:
            return json.load(f)
    except json.JSONDecodeError:
        return [] # Kembalikan list kosong jika file korup/kosong

def save_tasks(tasks):
    """Menyimpan list tugas ke file JSON."""
    with open(FILE_NAME, 'w') as f:
        json.dump(tasks, f, indent=4)

def show_tasks(tasks):
    """Menampilkan semua tugas."""
    if not tasks:
        print("Belum ada tugas.")
        return
    
    print("\n--- Daftar Tugas ---")
    for i, task in enumerate(tasks, 1):
        print(f"{i}. {task}")
    print("--------------------\n")

def add_task(tasks):
    """Menambahkan tugas baru."""
    task = input("Masukkan tugas baru: ")
    tasks.append(task)
    save_tasks(tasks)
    print(f"Tugas '{task}' telah ditambahkan.")

def remove_task(tasks):
    """Menghapus tugas berdasarkan nomor."""
    show_tasks(tasks)
    if not tasks:
        return
        
    try:
        num = int(input("Masukkan nomor tugas yang ingin dihapus: "))
        if 1 <= num <= len(tasks):
            removed_task = tasks.pop(num - 1)
            save_tasks(tasks)
            print(f"Tugas '{removed_task}' telah dihapus.")
        else:
            print("Nomor tidak valid.")
    except ValueError:
        print("Input tidak valid. Masukkan angka.")

def main():
    tasks = load_tasks()
    
    while True:
        print("\n===== Aplikasi To-Do List =====")
        print("1. Tampilkan Tugas")
        print("2. Tambah Tugas")
        print("3. Hapus Tugas")
        print("4. Keluar")
        
        choice = input("Pilih opsi (1-4): ")
        
        if choice == '1':
            show_tasks(tasks)
        elif choice == '2':
            add_task(tasks)
        elif choice == '3':
            remove_task(tasks)
        elif choice == '4':
            print("Terima kasih, sampai jumpa!")
            break
        else:
            print("Pilihan tidak valid.")

# Jalankan program utama
if __name__ == "__main__":
    main()
