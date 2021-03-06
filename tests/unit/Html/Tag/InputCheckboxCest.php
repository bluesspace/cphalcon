<?php
declare(strict_types=1);

/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalconphp.com>
 *
 * For the full copyright and license information, please view the LICENSE.txt
 * file that was distributed with this source code.
 */

namespace Phalcon\Test\Unit\Html\Tag;

use Phalcon\Test\Fixtures\Traits\DiTrait;
use Phalcon\Test\Fixtures\Traits\TagHelperTrait;
use Phalcon\Test\Fixtures\Traits\TagSetupTrait;

class InputCheckboxCest
{
    use DiTrait;
    use TagSetupTrait;
    use TagHelperTrait;

    protected $function  = 'inputCheckbox';
    protected $inputType = 'checkbox';
}
