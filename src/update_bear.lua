

function update_bear()
    print("updatting bear")
    darwin.dtw.remove_any("BearSSL")
    os.execute("git clone "..BEARSS_URL)
    darwin.dtw.move_any_overwriting("BearSSL/inc","origin/inc")
    darwin.dtw.move_any_overwriting("BearSSL/src","origin/src")
    darwin.dtw.remove_any("BearSSL")
end