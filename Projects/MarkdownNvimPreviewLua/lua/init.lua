local outputfile = "/tmp/output.html"

local function md_to_html(file)
	os.execute("pandoc -o " .. outputfile .. " " .. file)
end

local function open_html(file)
	os.execute(os.getenv("BROWSER") .. " " .. file)
end

local function preview(file)
	md_to_html(file)
	open_html(outputfile)
end

-- md_to_html(vim.api.nvim_buf_get_name(0))

-- vim.api.nvim_buf_set_keymap()

M = {}

M.preview = function ()
	preview(vim.api.nvim_buf_get_name(0))
end

return M
