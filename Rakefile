# task default: %w[build]

task :default do
  system "rake --tasks"
end

namespace :docker do

  desc "Build docs using docker"
  task :build do
    exec 'docker run --rm -i -t -v "${PWD}:/doc" -u "$(id -u):$(id -g)" ohiosupercomputer/ood-doc-build:v2.0.0 make html'
  end
end

desc "Open built documentation in browser"
task :open do
  exec '(command -v xdg-open >/dev/null 2>&1 && xdg-open build/html/index.html) || open build/html/index.html'
end

desc "Build docs using pipenv (shortcut)"
task :build => ["pipenv:build"]
task :clean => ["pipenv:clean"]
