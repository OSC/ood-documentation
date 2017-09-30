# task default: %w[build]

task :default do
  system "rake --tasks"
end

namespace :pipenv do
  desc "Build docs using pipenv"
  task :build do
    exec 'WORKDIR=/doc PIPENV_VENV_IN_PROJECT=1 pipenv run make html'
  end

  desc "Install pipenv dependencies"
  task :install do
    exec 'WORKDIR=/doc PIPENV_VENV_IN_PROJECT=1 pipenv install'
  end
end

namespace :docker do

  desc "Build docs using docker"
  task :build do
    exec 'docker run --rm -i -t -v "${PWD}:/doc" -u "$(id -u):$(id -g)" ohiosupercomputer/docker-sphinx make html'
  end
end

desc "Build docs using pipenv (shortcut)"
task :build => ["pipenv:build"]
