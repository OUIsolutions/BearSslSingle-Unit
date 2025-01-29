

function update_bear()
    print("updatting bear")
    darwin.dtw.remove_any("bear")
    os.execute("git clone "..BEARSS_URL)
end