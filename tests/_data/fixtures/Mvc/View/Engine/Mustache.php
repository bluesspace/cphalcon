<?php

/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalconphp.com>
 *
 * For the full copyright and license information, please view the LICENSE.txt
 * file that was distributed with this source code.
 */

namespace Phalcon\Test\Fixtures\Mvc\View\Engine;

use Mustache_Engine;
use Phalcon\DiInterface;
use Phalcon\Mvc\View\Engine;
use Phalcon\Mvc\View\EngineInterface;
use Phalcon\Mvc\ViewBaseInterface;

class Mustache extends Engine implements EngineInterface
{
    /**
     * The internal Mustache Engine
     * @var Mustache_Engine
     */
    protected $mustache;

    /**
     * The view params
     * @var array
     */
    protected $params = [];

    /**
     * Mustache constructor.
     */
    public function __construct(ViewBaseInterface $view, DiInterface $dependencyInjector = null)
    {
        $this->mustache = new Mustache_Engine();

        parent::__construct($view, $dependencyInjector);
    }

    /**
     * Renders a view using the template engine
     */
    public function render(string $path, $params, bool $mustClean = false)
    {
        if (!isset($params['content'])) {
            $params['content'] = $this->view->getContent();
        }

        $content = $this->mustache->render(
            file_get_contents($path),
            $params
        );

        if ($mustClean) {
            $this->view->setContent($content);
        } else {
            echo $content;
        }
    }
}
