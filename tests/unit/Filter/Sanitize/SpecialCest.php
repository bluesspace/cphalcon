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

namespace Phalcon\Test\Unit\Filter\Sanitize;

use Codeception\Example;
use Phalcon\Filter\Sanitize\Special;
use UnitTester;

class SpecialCest
{
    /**
     * Tests Phalcon\Filter\Sanitize\Special :: __invoke()
     *
     * @dataProvider getData
     *
     * @author       Phalcon Team <team@phalconphp.com>
     * @since        2018-11-13
     */
    public function filterSanitizeSpecialInvoke(UnitTester $I, Example $example)
    {
        $I->wantToTest('Filter\Sanitize\Special - __invoke()');

        $sanitizer = new Special();

        $actual = $sanitizer($example[0]);
        $I->assertEquals($example[1], $actual);
    }

    private function getData(): array
    {
        return [
            ['This is <html> tags', 'This is &#60;html&#62; tags'],
        ];
    }
}
