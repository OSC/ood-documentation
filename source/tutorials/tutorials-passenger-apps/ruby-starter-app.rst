.. _app-development-tutorials-passenger-apps-starter-ruby-app:

Starter Ruby Application
========================

This document walks through creating a hello world application in Ruby
with the `Sinatra`_ web framework.

config.ru for Sinatra
---------------------

The first thing we need for OnDemand to recognize this directory is a ``config.ru`` file.
For `Sinatra`_ this is the ``config.ru`` that you need.

.. code:: ruby

  # frozen_string_literal: true

  require_relative 'app'
  run App

config.ru for Ruby on Rails
---------------------------

This document does not cover `Ruby on Rails`_, but
this ``config.ru`` is given nonetheless for readers interested
in building Ruby apps based on `Ruby on Rails`_.

.. code:: ruby

  # frozen_string_literal: true

  require_relative 'config/environment'

  run Rails.application
  Rails.application.load_server

Install dependencies
--------------------

The application won't boot with just the ``config.ru``, though it will try.
What you need now is to install the gems (the ruby dependencies).

We need a ``Gemfile`` to tell ``bundler`` (Ruby's application for dependencies)
what gems to install. Here's that file.

.. code:: ruby

  # frozen_string_literal: true

  source 'https://rubygems.org'

  gem 'sinatra'

With the ``Gemfile`` written, we can now install the dependencies
into ``vendor/bundle``. Issue these commands to do that.

.. code:: shell

  bundle config path --local vendor/bundle
  bundle install


Write the app.rb file
---------------------

Still, the app will not boot at this point. The ``config.ru`` is looking
to load the ``app.rb`` file which does not exist yet.

The ``app.rb`` file that will actually import `Sinatra`_ and implement your routes.
Here's the simplest version of this file returning Hello World on the root URL.

.. code:: ruby

  require 'sinatra/base'

  class App < Sinatra::Base
    get '/' do
      'Hello World'
    end
  end


.. include:: deploy-to-production.inc

.. _Sinatra: https://sinatrarb.com/
.. _Ruby on Rails: https://rubyonrails.org/