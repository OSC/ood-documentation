
task :default do
  system "rake --tasks"
end

desc "Build docs using docker"
task :build do
  if podman?
    exec "podman run --rm -it -v #{__dir__}:/doc #{image} make html"
  elsif docker?
    exec "docker run --rm -it -v '#{__dir__}:/doc' -u '#{user_group}' #{image} make html"
  else
    raise StandardError, "Cannot find any suitable container runtime to build. Need 'podman' or 'docker' installed."
  end
end

desc "Open built documentation in browser"
task :open do
  exec '(command -v xdg-open >/dev/null 2>&1 && xdg-open build/html/index.html) || open build/html/index.html'
end

def user_group
  pwnam = Etc.getpwnam(Etc.getlogin)
  "#{pwnam.uid}:#{pwnam.gid}"
end

def image
  'ohiosupercomputer/ood-doc-build:v2.0.0'
end

def docker?
  `which docker 2>/dev/null 2>&1`
  $?.success?
end

def podman?
  `which podman 2>/dev/null 2>&1`
  $?.success?
end
