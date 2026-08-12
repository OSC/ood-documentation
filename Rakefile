
task :default do
  system "rake --tasks"
end

desc "Build docs using docker"
task :build do
  cmd = "#{run_cmd} make html"
  puts cmd
  exec cmd
end

desc "Clean workspace"
task :clean do
  exec "#{run_cmd} make clean"
end

desc "Spellcheck"
task :spellcheck do
  exec "#{run_cmd} make spellcheck"
end

desc "Open built documentation in browser"
task :open do
  if windows?
    system 'start .\build\html\index.html'
  elsif codespace?
    exec 'python -m http.server 8000 --directory build/html'
  else
    exec '(command -v xdg-open >/dev/null 2>&1 && xdg-open build/html/index.html) || open build/html/index.html'
  end
end

def user_group
  pwnam = Etc.getpwnam(Etc.getlogin)
  "#{pwnam.uid}:#{pwnam.gid}"
end

def image
  'ohiosupercomputer/ood-doc-build:v3.2.0'
end

def docker?
  exists? 'docker'
end

def podman?
  exists? 'podman'
end

def exists?(program)  
  `#{program} -v 2>/dev/null 2>&1`
  $?.success?
end

def windows?
  Gem.win_platform?
end

def codespace?
  ENV['CODESPACES'] == 'true'
end

def run_cmd
  if podman?
    "podman run --rm -it -v #{__dir__}:/doc #{image}"
  elsif docker?
    user_section = windows? ? nil : "-u '#{user_group}'"
    "docker run --rm -it -v \"#{__dir__}:/doc\" #{user_section} #{image}"
  else
    raise StandardError, "Cannot find any suitable container runtime to build. Need 'podman' or 'docker' installed."
  end
end
