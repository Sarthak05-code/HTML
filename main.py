import yt_dlp

url = input("Enter the YouTube URL: ")

ydl_opts = {"outtmpl": r"C:\Sarthak\%(title)s.%(ext)s"}

with yt_dlp.YoutubeDL(ydl_opts) as ydl:
    ydl.download([url])

print("Download completed!")
